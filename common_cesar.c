#include "common_cesar.h"

#include <stdio.h>

#define TAMANIO_ASCCI 256
#define EXITO 0


int cesar_inicializar(cesar_t* self, char* key){
    self->key = key;
    return EXITO;
}

int cesar_cifrado(cesar_t* self, unsigned char* mensaje, int tamanio, int formato){
    int key_aux = 0;
    key_aux = atoi(self->key);
    int i = 0;
    while (i<tamanio){
      mensaje[i] = (mensaje[i] + formato*key_aux) %TAMANIO_ASCCI;
      i++;
    }
    return EXITO;
}

int cesar_destruir(cesar_t* self){
    return EXITO;
}
