#ifndef _CLIENT_CLIENTE_H
#define _CLIENT_CLIENTE_H

#include "common_socket.h"
#include "common_encriptadores.h"
#include "client_lector.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include <string.h>


#define TAMANIO_MAXIMO 200

typedef struct cliente{
    encriptador_t encriptador;
    socket_t socket;
    lector_t lector;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    char funcion[TAMANIO_MAXIMO];
    char key[TAMANIO_MAXIMO];
    char host[TAMANIO_MAXIMO];
    char service[TAMANIO_MAXIMO];
}cliente_t;

/*
  * Inicializara la estructra cliente, creando sus respectivos atrituvos
  * La dejara valida para uso
  * devolver error si no la pude crear sino exito
*/
int cliente_inicializar(cliente_t* self, char host[TAMANIO_MAXIMO],
                        char key[TAMANIO_MAXIMO], char service[TAMANIO_MAXIMO],
                        char funcion[TAMANIO_MAXIMO], char* argv[]);
/*
  * Ejecutara las instrucciones que le corresponde a un cliente
  * ejemplo: conect
*/
int cliente_run(cliente_t* self);
/*
  * Se encragra de liberar las distintas entidades que conforman a la
  * estructura
*/  
int cliente_destruir(cliente_t* self);

#endif
