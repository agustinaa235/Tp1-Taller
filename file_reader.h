#ifndef _FILE_READER_H
#define _FILE_READER_H

#include  <stdio.h>


typedef struct lector {
      FILE* file;
}lector_t;



typedef void (*lector_callback_t)(const char* mensaje, int tamanio_mensaje,void* callback_ctx);
typedef void (*lector_callback2_t)(void* callback_2, const char* mensaje);

int lector_inicializar(lector_t* self, const char* file_nombre);
int lector_iterar(lector_t* self, lector_callback_t callback, lector_callback2_t callback2, void* callback_ctx, void* callback_2);
int lector_destruir(lector_t* self);


#endif
