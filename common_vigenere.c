#include "common_vigenere.h"
#include <string.h>
#define ASCCI 256
#define EXITO 0

int vigenere_inicializar(vigenere_t* self, char* key){
    self->key = key;
    self->pos_key = 0;
    return EXITO;
}

int vigenere_cifrado(vigenere_t* self, unsigned char* mensaje, int tamanio,
                     int formato){
    int i = 0;
    while (i< tamanio){
        if ((self->pos_key) == strlen(self->key)){
              self->pos_key = 0;
        }
        mensaje[i] = (mensaje[i] + formato*(self->key[self->pos_key]))%ASCCI;
        i++;
        (self->pos_key)++;
    }
  return EXITO;
}

int vigenere_destruir(vigenere_t* self){
    return EXITO;
}
