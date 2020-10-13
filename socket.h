#ifndef _SOCKET_H
#define _SOCKET_H

#include <stddef.h>
#include <stdint.h>

typedef struct socket {
   int socket;
}socket_t;

int socket_inicializar(socket_t* self);
void socket_destruir(socket_t* self);
int socket_bine_and_listen(socket_t* self, const char* host, const char* service);
int socket_acceptar(socket_t* listener, socket_t* peer);
int socket_conectar(socket_t* self, const char* host, const char* service);
size_t socket_enviar(socket_t* self, const char* mensaje, size_t tamanio);
size_t socket_recibir(socket_t* self, char* mensaje, size_t tamanio);


#endif
