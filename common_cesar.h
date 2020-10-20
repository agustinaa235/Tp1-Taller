#ifndef _COMMON_CESAR_H
#define _COMMON_CESAR_H

typedef struct cesar {
      char* key;
} cesar_t;



int cesar_inicializar(cesar_t* self, char* key);

int cesar_cifrado(cesar_t* self, unsigned char* mensaje, int tamanio,
                  int formato);

int cesar_destruir(cesar_t* self);


#endif
