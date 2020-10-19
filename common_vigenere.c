#include "common_vigenere.h"

#define TAMANIO_ASCCI 256
#define EXITO 0

int vigenere_inicializar(vigenere_t* self, char* key){
    self->key = 0;
    self->posicion_key = 0;
    return EXITO;
}

int vigenere_cifrado(vigenere_t* self, unsigned char* mensaje, int tamanio, int formato){

    int i = 0;
    while (i< tamanio){
        if ((self->posicion_key) == strlen(self->key)){
              self->posicion_key = 0;
        }
        mensaje[i] = (mensaje[i] + formato*(self->key[self->posicion_key]))% TAMANIO_ASCCI;
        i++;
        (self->posicion_key)++;
    }
  return EXITO;
}

int vigenere_destruir(vigenere_t* self){
    return EXITO;
}
