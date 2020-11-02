#ifndef _COMMON_SOCKET_H
#define _COMMON_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <netdb.h>

typedef void (*socket_desencriptacion_t)(void* callback_encriptador,
                                          const char* mensaje,
                                          int tamanio);

typedef struct socket {
   int file_descriptor;
}socket_t;

/*
  * inicializara la estructura con -1 para luego inicializarla
  * en un bine o en un connect
*/
int socket_inicializar(socket_t* self);
/*
  * hara un bine y luego un listene
  * si falla algo devolvera error sino devolvera exito
*/
int socket_bine_and_listen(socket_t* self,
                           const char* host,
                           const char* service);
/*
  * se creara el socket peer en caso de que le llegue un connect
  *si no existe el listerner cerrara ese socket y saldra de la
  *funcione
*/
int socket_acceptar(socket_t* listener, socket_t* peer);
/*
  * Hara un conect y asociaria ese socket con el que recibe la funcion
  * por referencia
  * Si falla algo se devolvera error, sino devolvera exito
*/
int socket_conectar(socket_t* self, const char* host, const char* service);
/*
  * enviara el mensaje que recibe por parametro
  * si hay una falla devolvera error, sino devolvera exito
*/
int socket_enviar(socket_t* self, const char* mensaje, size_t tamanio);
/*
  * recibira el mensaje, lo desencriptara y lo imprimira por salida estandar
  * si falla algo devolvera error sino devolvera exito
*/
int socket_recibir(socket_t* self, char* mensaje, size_t tamanio);
/*
  * destruirra la estrcutura haciendo un shoutdown y luego un close
*/
void socket_destruir(socket_t* self);

#endif
