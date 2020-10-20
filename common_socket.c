#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <stdbool.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define ESCUCHA 5
#define ERROR 1
#define EXITO 0
#define FALLA_SOCKET -1
#define EXITO_GET_ADD_INFO 0


int socket_inicializar(socket_t* self){
    self->file_descriptor = -1;
    return EXITO;
}
void inicializar_struct_hints(struct addrinfo* hints, int ai_family,
                              int ai_socktype, int ai_flags){
      memset(hints, 0, sizeof(struct addrinfo));
      hints->ai_family = ai_family;
      hints->ai_socktype = ai_socktype;
      hints->ai_flags = ai_flags;
}

int socket_bine_and_listen(socket_t* self,
                           const char* host,
                           const char* service){
      bool hubo_un_error = false;
      struct addrinfo hints, *resultado, *rp;
      inicializar_struct_hints(&hints,AF_INET, SOCK_STREAM, AI_PASSIVE);
      if (getaddrinfo(host, service, &hints, &resultado) != EXITO_GET_ADD_INFO){
          return ERROR;
      }
      rp = resultado;
      while (rp != NULL && hubo_un_error == false){
          int file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                       rp->ai_protocol);
          if (file_descriptor == FALLA_SOCKET){
              hubo_un_error = true;
          } else {
              if (bind(file_descriptor, rp->ai_addr, rp->ai_addrlen)
                        == FALLA_SOCKET){
                  close(file_descriptor);
                  hubo_un_error = true;
              } else {
                  self->file_descriptor = file_descriptor;
              }
          }
          rp = rp->ai_next;
      }
      if (hubo_un_error){
          return ERROR;
      }
      freeaddrinfo(resultado);
      if (listen(self->file_descriptor, ESCUCHA) == FALLA_SOCKET){
          return ERROR;
      }
      return EXITO;
}

int socket_acceptar(socket_t* listener, socket_t* peer){
      if (listener->file_descriptor == FALLA_SOCKET){
          return ERROR;
      }
      peer->file_descriptor = accept(listener->file_descriptor, NULL, NULL);
      if (peer->file_descriptor == FALLA_SOCKET){
          close(listener->file_descriptor);
          return ERROR;
      }
      return EXITO;
}

int socket_conectar(socket_t* self, const char* host, const char* service){
    bool hubo_un_error = false;
    struct addrinfo hints, *resultado, *aux;
    inicializar_struct_hints(&hints,AF_INET, SOCK_STREAM, 0);
    if (getaddrinfo(host, service, &hints, &resultado) != EXITO_GET_ADD_INFO){
        return ERROR;
    }
    aux = resultado;
    while (aux != NULL && hubo_un_error == false){
        int file_descriptor = socket(aux->ai_family, aux->ai_socktype,
                                     aux->ai_protocol);
        if (file_descriptor == FALLA_SOCKET){
            hubo_un_error = true;
        } else {
            if (connect(file_descriptor,aux->ai_addr,aux->ai_addrlen)
                        == FALLA_SOCKET){
                close(file_descriptor);
                hubo_un_error = true;
            } else {
                self->file_descriptor = file_descriptor;
            }
        }
        aux = aux->ai_next;
    }
    freeaddrinfo(resultado);
    if (hubo_un_error){
        return ERROR;
    }
    return EXITO;
}

int socket_enviar(socket_t* self, const char* mensaje, size_t tamanio){
    if (self->file_descriptor == FALLA_SOCKET){
        return ERROR;
    }
    int bytes_enviados = 0;
    bool hubo_un_error = false;
    while (bytes_enviados < tamanio && hubo_un_error == false) {
        int verificacion = send(self->file_descriptor, &mensaje[bytes_enviados],
                                (tamanio - bytes_enviados), MSG_NOSIGNAL);
        if (verificacion > 0) {
            bytes_enviados += verificacion;
        } else {
            hubo_un_error = true;
        }
    }
    if (hubo_un_error){
        return ERROR;
    }
    return EXITO;
}

int socket_recibir(socket_t* self, char* mensaje, size_t tamanio,
                   socket_callback_t callback, void* callback_3){
    if (self->file_descriptor == FALLA_SOCKET){
          return ERROR;
    }
    bool hubo_un_error = false;
    int bytes_recibidos = 0;
    bool se_cerro_el_socket = false;
    while (hubo_un_error == false && se_cerro_el_socket == false) {
        int verificacion = recv(self->file_descriptor,&mensaje[bytes_recibidos],
                                (tamanio - bytes_recibidos-1), 0);
        if (verificacion == -1) {
            hubo_un_error = true;
        } else if (verificacion == 0) {
            se_cerro_el_socket = true;
        } else {
            bytes_recibidos += verificacion;
            callback(callback_3, mensaje, bytes_recibidos);
            mensaje[bytes_recibidos] = '\0';
            fwrite(mensaje, 1, bytes_recibidos, stdout);
            bytes_recibidos = 0;
        }
      }
      if (hubo_un_error) {
          return ERROR;
      } else {
          return EXITO;
      }
}
void socket_destruir(socket_t* self){
    if (self->file_descriptor > 0){
        shutdown(self->file_descriptor, SHUT_RDWR);
        close(self->file_descriptor);
    }
}
