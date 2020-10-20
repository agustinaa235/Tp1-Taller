#ifndef _COMMON_RC4_H
#define _COMMON_RC4_H

#define TAMANIO_VECTOR_KS 256

typedef struct rc4 {
      char* key;
      unsigned char key_stream[TAMANIO_VECTOR_KS];
      int pos_j;
      int pos_k;
} rc4_t;

/*
  * inicializar la estructa rc4 dejando la valida para usa
*/
int rc4_inicializar(rc4_t* self, char* key);
/*
  * cifrara el mensaje que le llegue con el correspondiente formato
  * este mensaje debe ser valido
*/
int rc4_cifrado(rc4_t* self, unsigned char* mensaje, int tamanio, int formato);
/*
  * destruira la estructura
*/  
int rc4_destruir(rc4_t* self);


#endif
