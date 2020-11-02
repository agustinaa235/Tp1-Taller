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
/*
  * Inicializa la estructura hint dejandola valida
*/
void inicializar_struct_hints(struct addrinfo* hints, int ai_family,
                              int ai_socktype, int ai_flags){
      memset(hints, 0, sizeof(struct addrinfo));
      hints->ai_family = ai_family;
      hints->ai_socktype = ai_socktype;
      hints->ai_flags = ai_flags;
}
/*
  * funcion auxiliar en donde se invoca la funcion bine del socket
*/
int bine_aux(int file_descriptor, struct addrinfo* rp){
    return bind(file_descriptor, rp->ai_addr, rp->ai_addrlen);
}
/*
  * funcion auxiliar en donde se invoca la funcion connect del socket
*/
int connect_aux(int file_descriptor, struct addrinfo* rp){
    return connect(file_descriptor, rp->ai_addr, rp->ai_addrlen);
}
/*
  * En esta funcion se itera por la lista que devuelve getaddrino tratando de
  *hacer una conexcion con el socket que recibe y luego tratar de concetarse
  * a la funcion que recibe como puntero, para el caso del bine_and_listen
  * recibe bine_aux y para el caso del connectar recibe connect_aux
  * devulve si se pudo hacer la correspondiente conexcion o no.
*/
bool iteracion_lista_getaddrinfo(socket_t* self, struct addrinfo* rp,
                                int(*funcion_correspondiente_a_llamada_socket)
                                (int,struct addrinfo*)){
    bool hubo_un_error = true;
    while (rp != NULL && hubo_un_error){
        int file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                   rp->ai_protocol);
        if (file_descriptor == FALLA_SOCKET){
            hubo_un_error = true;
        } else {
            if (funcion_correspondiente_a_llamada_socket(file_descriptor, rp)
                  == FALLA_SOCKET){
                close(file_descriptor);
                hubo_un_error = true;
            } else {
                hubo_un_error = false;
                self->file_descriptor = file_descriptor;
            }
        }
        rp = rp->ai_next;
    }
    return hubo_un_error;
}

int socket_bine_and_listen(socket_t* self,
                           const char* host,
                           const char* service){
      bool no_pude_binear = true;
      struct addrinfo hints, *resultado, *rp;
      inicializar_struct_hints(&hints,AF_INET, SOCK_STREAM, AI_PASSIVE);
      if (getaddrinfo(host, service, &hints, &resultado) != EXITO_GET_ADD_INFO){
          return ERROR;
      }
      rp = resultado;
      no_pude_binear = iteracion_lista_getaddrinfo(self, rp, bine_aux);
      if (no_pude_binear){
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
    bool no_hubo_conexion = true;
    struct addrinfo hints, *resultado, *aux;
    inicializar_struct_hints(&hints,AF_INET, SOCK_STREAM, 0);
    if (getaddrinfo(host, service, &hints, &resultado) != EXITO_GET_ADD_INFO){
        return ERROR;
    }
    aux = resultado;
    no_hubo_conexion = iteracion_lista_getaddrinfo(self, aux, connect_aux);
    freeaddrinfo(resultado);
    if (no_hubo_conexion){
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
int socket_recibir(socket_t* self, char* mensaje, size_t tamanio){
    if (self->file_descriptor == FALLA_SOCKET){
          return ERROR;
    }
    int bytes_recibidos = 0;
    int verificacion = recv(self->file_descriptor,&mensaje[bytes_recibidos],
                            (tamanio - bytes_recibidos -1), 0);
    return verificacion;
}

void socket_destruir(socket_t* self){
    if (self->file_descriptor > 0){
        shutdown(self->file_descriptor, SHUT_RDWR);
        close(self->file_descriptor);
    }
}
