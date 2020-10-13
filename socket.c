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

    self->socket = socket (AF_INET, SOCK_DGRAM, 0);
    if (self->socket < 0){
        return ERROR;
    }
    return EXITO;

}

int socket_bine_and_listen(socket_t* self, const char* host, const char* service){
      int verificacion = 0;
      struct addrinfo hints;
      struct addrinfo *resultado;
      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = 0;

      verificacion = getaddrinfo(host, service, &hints, &resultado);
      if (verificacion != 0){
          return ERROR;
      }

      //bind( sockfd,(struct sockaddr *)&resultado, (socklen_t)sizeof(struct sockaddr)) < 0)
      if (bind(self->socket, resultado->ai_addr, resultado->ai_addrlen) < 0){
          close(self->socket);
          freeaddrinfo(resultado);
          return ERROR;
      };

      verificacion = listen(self->socket, ESCUCHA_POR_CONEXIONES);
      if( verificacion != 0){
          return ERROR;
      }

}


int socket_acceptar(socket_t* listener, socket_t* peer){
      peer->socket = accept(listener->socket, NULL, NULL);
      if(peer->socket == -1){
          return ERROR;
      };
      return EXITO;
}

int socket_conectar(socket_t* self, const char* host, const char* service){
    int verificacion = 0;
    bool conectado = false;
    struct addrinfo hints;
    struct addrinfo *resultado, *auxiliar;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

    verificacion = getaddrinfo(host, service, &hints, &resultado);
    if(verificacion != 0){
        return ERROR;
    }

    for (auxiliar = resultado; auxiliar != NULL && conectado == false; auxiliar = auxiliar->ai_next) {
       /* Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
          el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0) */
          /* Nos conectamos a la fiuba
             ai_addr encapsula la IP y el puerto del server.
             La estructura es automaticamente creada por getaddrinfo */
          verificacion = connect(self->socket, auxiliar->ai_addr, auxiliar->ai_addrlen);
          if (verificacion == -1) {
             printf("Error: %s\n", strerror(errno));
             close(self->socket);
          }
          conectado = (verificacion != -1); // nos conectamos?
       }
    freeaddrinfo(resultado);
}

size_t socket_enviar(socket_t* self, const char* mensaje, size_t tamanio){

    int bytes_enviados = 0;
    bool estamos_conectados = true;
    int verificacion = 0;
    while (bytes_enviados < tamanio && estamos_conectados) {
        verificacion = send(self->socket, &mensaje, tamanio - bytes_enviados, MSG_NOSIGNAL);
        if (verificacion > 0) {
            bytes_sent += verificacion;
        } else {
            printf("Error: %s\n", strerror(errno));
            estamos_conectados = false;
        }
    }
}

void socket_destruir(socket_t* self){

    close(self->socket);
}
