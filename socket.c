#include "socket.h"

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

int socket_bine_and_listen(socket_t* self, const char* host, const char* service){
      int verificacion = 0;
      int file_descriptor = -2;
      bool no_pude_binear = true;
      struct addrinfo hints;
      struct addrinfo *resultado, *rp;
      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;

      verificacion = getaddrinfo(host, service, &hints, &resultado);
      if (verificacion != 0){
          printf(" no funciona get addrinfo");
          return ERROR;
      }
      rp = resultado;
      while(rp != NULL && no_pude_binear){

          file_descriptor = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            printf(" file descriptro: %i\n", file_descriptor);
          if (file_descriptor == -1){
              printf("Error: %s\n", strerror(errno));
              printf(" no creo el socket");
          } else {
              if (bind(file_descriptor, rp->ai_addr, rp->ai_addrlen) == -1){
                  close(file_descriptor);
                  printf(" no pude binear");
                  printf("Error: %s\n", strerror(errno));
              } else {
                  no_pude_binear = false;
                  self->file_descriptor = file_descriptor;
                  printf(" binie");
              }
          }
          rp = rp->ai_next;
      }

      if (no_pude_binear){
          printf(" no me concete");
          return ERROR; // no nos pudimos concetar a nnguna dirreccion
      }

      freeaddrinfo(resultado);
      verificacion = listen(self->file_descriptor, ESCUCHA_POR_CONEXIONES);
      if( verificacion != 0){
          return ERROR;
      }
      return EXITO;

}


int socket_acceptar(socket_t* listener, socket_t* peer){
      peer->file_descriptor = accept(listener->file_descriptor, NULL, NULL);
      if(peer->file_descriptor == -1){
          return ERROR;
      }
      return EXITO;
}

int socket_conectar(socket_t* self, const char* host, const char* service){
    int file_descriptor = -2;

    bool no_conectado = true;
    struct addrinfo hints;
    struct addrinfo *resultado, *auxiliar;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

    if (getaddrinfo(host, service, &hints, &resultado) != 0){
        printf("Error: %s\n", strerror(errno));
        printf("no funciona getaddrinfo");
        return ERROR;
    }
    auxiliar = resultado;
    while(auxiliar != NULL && no_conectado){
        file_descriptor = socket(auxiliar->ai_family, auxiliar->ai_socktype, auxiliar->ai_protocol);
        printf(" file descriptro: %i\n", file_descriptor);
        if (file_descriptor < 0){
            printf("Error: %s\n", strerror(errno));
            printf("no creo el socket\n");
        } else {
            if(connect(file_descriptor, auxiliar->ai_addr, auxiliar->ai_addrlen) == -1){
                close(file_descriptor);
                printf("no pude concetarme\n");
            } else {
                no_conectado = false;
                self->file_descriptor = file_descriptor;
                printf(" si me concete\n");
            }
        }
        auxiliar = auxiliar->ai_next;
    }
    freeaddrinfo(resultado);
    if (no_conectado == true){
        printf(" no me concete");
        return ERROR; // no nos pudimos concetar a nnguna dirreccion
    }
    return EXITO;
}

int socket_enviar(socket_t* self, const char* mensaje, size_t tamanio){

    int bytes_enviados = 0;
    bool hubo_un_error = false;
    int verificacion = 0;
    while (bytes_enviados < tamanio && hubo_un_error == false) {
        verificacion = send(self->file_descriptor, &mensaje[bytes_enviados], (tamanio - bytes_enviados), MSG_NOSIGNAL);
        if (verificacion > 0) {
            bytes_enviados += verificacion;
            printf(" bytes enviados\n: %i", bytes_enviados);
        } else {
            printf("Error: %s\n", strerror(errno));
            hubo_un_error = true;
        }
    }
    if(hubo_un_error){
        return ERROR;
    }
    return EXITO;
}

int socket_recibir(socket_t* self, char* mensaje, size_t tamanio){

    int verificacion = 0;
    bool hubo_un_error = false;
    int bytes_recibidos = 0;
    bool se_cerro_el_socket = false;
    while (hubo_un_error == false && se_cerro_el_socket == false) {
        verificacion = recv(self->file_descriptor, &mensaje[bytes_recibidos], (tamanio - bytes_recibidos - 1), 0);

        if (verificacion == -1) {
            printf("Error: %s\n", strerror(errno));
            hubo_un_error = true;
        } else if (verificacion == 0) {

            se_cerro_el_socket = true;
        } else {
            bytes_recibidos += verificacion;
        }
    }


    if (hubo_un_error) {
      return ERROR;   // hubo un error, somos consistentes y salimos con un codigo de error
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
