#ifndef _COMMON_RC4_H
#define _COMMON_RC4_H

#define TAMANIO_VECTOR_KS 256

typedef struct rc4 {
      char* key;
      unsigned char key_stream[TAMANIO_VECTOR_KS];
      int pos_j;
      int pos_k;
} rc4_t;

int rc4_inicializar(rc4_t* self, char* key);

int rc4_cifrado(rc4_t* self, unsigned char* mensaje, int tamanio, int formato);

int rc4_destruir(rc4_t* self);


#endif
