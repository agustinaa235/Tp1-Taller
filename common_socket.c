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

#define ESCUCHA_POR_CONEXIONES 5
#define ERROR 1
#define EXITO 0


int socket_inicializar(socket_t* self){
    self->file_descriptor = -1;
    return EXITO;
}

int socket_bine_and_listen(socket_t* self,
                           const char* host,
                           const char* service){
      int verificacion = 0;
      bool no_pude_binear = true;
      struct addrinfo hints;
      struct addrinfo *resultado, *rp;
      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;

      verificacion = getaddrinfo(host, service, &hints, &resultado);
      if (verificacion != 0){
          return ERROR;
      }
      rp = resultado;
      while (rp != NULL && no_pude_binear){
          int file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                       rp->ai_protocol);
          if (file_descriptor == -1){
          } else {
              if (bind(file_descriptor, rp->ai_addr, rp->ai_addrlen) == -1){
                  close(file_descriptor);
              } else {
                  no_pude_binear = false;
                  self->file_descriptor = file_descriptor;
              }
          }
          rp = rp->ai_next;
      }
      if (no_pude_binear){
          return ERROR; // no nos pudimos concetar a nnguna dirreccion
      }
      freeaddrinfo(resultado);
      verificacion = listen(self->file_descriptor, ESCUCHA_POR_CONEXIONES);
      if (verificacion != 0){
          return ERROR;
      }
      return EXITO;
}

int socket_acceptar(socket_t* listener, socket_t* peer){
      peer->file_descriptor = accept(listener->file_descriptor, NULL, NULL);
      if (peer->file_descriptor == -1){
          return ERROR;
      }
      return EXITO;
}

int socket_conectar(socket_t* self, const char* host, const char* service){
    bool no_conectado = true;
    struct addrinfo hints;
    struct addrinfo *resultado, *aux;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

    if (getaddrinfo(host, service, &hints, &resultado) != 0){
        return ERROR;
    }
    aux = resultado;
    while (aux != NULL && no_conectado){
        int file_descriptor = socket(aux->ai_family, aux->ai_socktype,
                                     aux->ai_protocol);
        if (file_descriptor < 0){
            no_conectado = true;
        } else {
            if (connect(file_descriptor,aux->ai_addr,aux->ai_addrlen)== -1){
                close(file_descriptor);
            } else {
                no_conectado = false;
                self->file_descriptor = file_descriptor;
            }
        }
        aux = aux->ai_next;
    }
    freeaddrinfo(resultado);
    if (no_conectado == true){
        return ERROR; // no nos pudimos concetar a nnguna dirreccion
    }
    return EXITO;
}

int socket_enviar(socket_t* self, const char* mensaje, size_t tamanio){
    int bytes_enviados = 0;
    bool hubo_un_error = false;
    while (bytes_enviados < tamanio && hubo_un_error == false) {
        int verificacion = send(self->file_descriptor, &mensaje[bytes_enviados],
                                (tamanio - bytes_enviados), MSG_NOSIGNAL);
        if (verificacion > 0) {
            bytes_enviados += verificacion;
        } else {
            printf("Error: %s\n", strerror(errno));
            hubo_un_error = true;
        }
    }
    if (hubo_un_error){
        return ERROR;
    }
    return EXITO;
}

int socket_recibir(socket_t* self,
                   char* mensaje,
                   size_t tamanio,
                   socket_callback_t callback,
                   void* callback_3){
    bool hubo_un_error = false;
    int bytes_recibidos = 0;
    bool se_cerro_el_socket = false;
    while (hubo_un_error == false && se_cerro_el_socket == false) {
        int verificacion = recv(self->file_descriptor,&mensaje[bytes_recibidos],
                                (tamanio - bytes_recibidos - 1), 0);
        if (verificacion == -1) {
            printf("Error: %s\n", strerror(errno));
            hubo_un_error = true;
        } else if (verificacion == 0) {
            se_cerro_el_socket = true;
        } else {
            bytes_recibidos += verificacion;
            callback(callback_3, mensaje);
            mensaje[bytes_recibidos] = '\0';
            fwrite(mensaje, 1, bytes_recibidos, stdout);
            bytes_recibidos = 0;
        }
        printf("\n");
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
