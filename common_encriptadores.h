#ifndef _COMMON_ENCRIPTADORES_H
#define _COMMON_ENCRIPTADORES_H

typedef struct encriptador {
      char* funcion;
      void* tipo_de_encriptador;
} encriptador_t;

/*
  * inicializara la estructura con una funcion valida
  * y un tipo de encriptador valido dejando la estructura
  *valida para uso
*/
int encriptador_inicializar(encriptador_t *self, char* funcion,
                            void* tipo_de_encriptador);
/*
  * se encarga de encriptar el mensaje que recibe por parametro
  * el mensaje lo toma como valido
*/
int encriptador_encriptar(encriptador_t *self, unsigned char* mensaje,
                          int tamanio);
/*
  * se encarga de dencriptar el mensaje que recibe por parametro
  * el mensaje lo toma como valido
*/
int encriptador_desencriptar(encriptador_t* self, unsigned char* mensaje,
                              int tamanio);
/*
  * se encarga de destruir la estrcutura destrutendo todos sus atributos
*/
int encriptador_destruir(encriptador_t *self);

#endif
