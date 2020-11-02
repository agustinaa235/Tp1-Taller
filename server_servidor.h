#ifndef _SERVER_SERVIDOR_H
#define _SERVER_SERVIDOR_H

#include "common_socket.h"
#include "common_encriptadores.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include <string.h>

#define TAMANIO_MAXIMO 200

typedef struct servidor{
    encriptador_t encriptador;
    socket_t socket;
    socket_t peer;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    char funcion[TAMANIO_MAXIMO];
    char key[TAMANIO_MAXIMO];
    char host[TAMANIO_MAXIMO];
    char service[TAMANIO_MAXIMO];
}servidor_t;

/*
  * Inicializara a la estructura servidor.
  * Tambien inicializara a las distintas entidades que necesiata este servidor
  * Devolvera error si no pudo crear algo, sino devolvera exito
*/
int servidor_inicializar(servidor_t* self, char service[TAMANIO_MAXIMO],
                         char funcion[TAMANIO_MAXIMO], char key[TAMANIO_MAXIMO],
                         char* argv[]);
/*
  * Ejecutara las instrucciones que les corresponde de un servidor
  * En este caso, bine and listen, aceptar y la logica de desencriptacion
*/
int servidor_run(servidor_t* self);
/*
  * Se encargara de liberar los recursos necesarios de los atributos
  que se guarda y a ella misma.
*/
int servidor_destruir(servidor_t* self);

#endif
