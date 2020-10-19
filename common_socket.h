#ifndef _COMMON_SOCKET_H
#define _COMMON_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <netdb.h>

typedef void (*socket_callback_t)(void* callback_3, const char* mensaje,
                                  int tamanio);

typedef struct socket {
   int file_descriptor;
}socket_t;

int socket_inicializar(socket_t* self);
void socket_destruir(socket_t* self);
int socket_bine_and_listen(socket_t* self,
                           const char* host,
                           const char* service);
int socket_acceptar(socket_t* listener, socket_t* peer);
int socket_conectar(socket_t* self, const char* host, const char* service);
int socket_enviar(socket_t* self, const char* mensaje, size_t tamanio);
int socket_recibir(socket_t* self, char* mensaje, size_t tamanio,
                   socket_callback_t callback, void* callback_3);


#endif
