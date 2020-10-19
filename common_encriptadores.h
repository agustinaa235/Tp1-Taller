#ifndef _COMMON_ENCRIPTADORES_H
#define _COMMON_ENCRIPTADORES_H


typedef struct encriptador {
      char* funcion;
      void* tipo_de_encriptador;
} encriptador_t;

int encriptador_inicializar(encriptador_t *self,const char* funcion,
                            void* tipo_de_encriptador);

int encriptador_encriptar(encriptador_t *self, unsigned char* mensaje,
                          int tamanio);

int encriptador_desencriptar(encriptador_t* self, unsigned char* mensaje,
                              int tamanio);

int encriptador_destruir(encriptador_t *self);


#endif
