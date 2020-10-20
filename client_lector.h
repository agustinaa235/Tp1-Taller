#ifndef _CLIENT_LECTOR_H
#define _CLIENT_LECTOR_H

#include  <stdio.h>


typedef struct lector {
      FILE* file;
}lector_t;

typedef void (*lector_callback_t)(const char* mensaje,
                                  int tamanio_mensaje,
                                  void* callback_ctx);
typedef void (*lector_callback2_t)(void* callback_2, const char* mensaje,
                                   int cant_leidos);
/*
  *inicializara la estructura defandola valida
    * si el file nombre es null toma el de entrada estandar
    *si no puede abrir el archivo devuelve error sino devuelve exito
*/
int lector_inicializar(lector_t* self, const char* file_nombre);
/*
  *leera del archivo y mientras va leyendo invoca a callback y callback_2
  * si falla fread devuelve error sino devuelve exito
*/
int lector_iterar(lector_t* self,
                  lector_callback_t callback,
                  lector_callback2_t callback2,
                  void* callback_ctx, void* callback_2);
/*
  * destruira la estructura haciendo un fclose
*/
int lector_destruir(lector_t* self);

#endif
