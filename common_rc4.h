#ifndef _COMMON_RC4_H
#define _COMMON_RC4_H

typedef struct rc4 {
      char* key;

} rc4_t;



int rc4_inicializar(rc4_t* self, char* key);

int rc4_cifrado(rc4_t* self, unsigned char* mensaje, int tamanio, int formato);

int rc4_destruir(rc4_t* self);


#endif
