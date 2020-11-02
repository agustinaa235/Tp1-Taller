#include "common_rc4.h"
#include <stdio.h>
#include <string.h>
#define TAMANIO_VECTOR_KS 256
#define EXITO 0

/*
  * realiza un intercambio
*/
void swap(unsigned char* key_stream, int j, int k) {
    unsigned char aux = key_stream[j];
    key_stream[j] = key_stream[k];
    key_stream[k] = aux;
}
/*
  * esta funcion realiza el algortimo de inicializar el key_stream
  * y dejarlo valido
*/
static unsigned char* rc4_ksa(char* key,
                              unsigned char key_stream[TAMANIO_VECTOR_KS]){
    int j = 0;
    for (int i = 0; i < (TAMANIO_VECTOR_KS); i++){
        key_stream[i] = i;
    }
    for (int x = 0; x < (TAMANIO_VECTOR_KS); x++) {
        j = (j + key[x % strlen(key)] + key_stream[x])%TAMANIO_VECTOR_KS;
        swap(key_stream, x, j);
    }
    return key_stream;
}

int rc4_inicializar(rc4_t* self, char* key){
    self->key = key;
    rc4_ksa(key, self->key_stream);
    self->pos_j = 0;
    self->pos_k = 0;
    return EXITO;
}
/*
  * esta funcion se encarga de realizar el algorimo de encroptacion del mensaje
  * con la key_stream
*/
static unsigned char rc4_prga(unsigned char* key_stream, int* j, int* k) {
    *j = (*j + 1) % TAMANIO_VECTOR_KS;
    *k = (*k + key_stream[*j])%TAMANIO_VECTOR_KS;
    swap(key_stream, *j, *k);
    return key_stream[((key_stream[*j] + key_stream[*k]) % TAMANIO_VECTOR_KS)];
}


int rc4_cifrado(rc4_t* self, unsigned char* mensaje, int tamanio, int formato){
    int i = 0;
    while (i< tamanio){
        mensaje[i] = mensaje[i]^rc4_prga(self->key_stream, &self->pos_j,
                                         &self->pos_k);
        i++;
    }
    return EXITO;
}

int rc4_destruir(rc4_t* self){
    return EXITO;
}
