#include "common_encriptadores.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"

#include <stdio.h>
#include <string.h>

#define EXITO 0
#define ERROR 0
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"


int encriptador_inicializar(encriptador_t *self, char* funcion,
                            void* tipo_de_encriptador){
    self->funcion = funcion;
    self->tipo_de_encriptador = tipo_de_encriptador;
    return EXITO;
}

int encriptador_verificar_encriptacion(encriptador_t* self,
                                       unsigned char* mensaje, int tamanio,
                                       int formato){
    if (strcmp(self->funcion, CESAR) == 0){
        return cesar_cifrado((cesar_t*)self->tipo_de_encriptador, mensaje,
                              tamanio, formato);
    } else if (strcmp(self->funcion, VIGENERE) == 0){
        return vigenere_cifrado((vigenere_t*)self->tipo_de_encriptador, mensaje,
                                 tamanio, formato);
    } else if (strcmp(self->funcion, RC4) == 0){
        return rc4_cifrado((rc4_t*)self->tipo_de_encriptador,mensaje, tamanio,
                            formato);
    } else {
        return ERROR;
    }
}

int encriptador_encriptar(encriptador_t *self, unsigned char* mensaje,
                          int tamanio){
      return encriptador_verificar_encriptacion(self, mensaje, tamanio, 1);
}
int encriptador_desencriptar(encriptador_t* self, unsigned char* mensaje,
                             int tamanio){
      return encriptador_verificar_encriptacion(self, mensaje, tamanio, -1);
}

int destruir_tipo_de_encriptador(encriptador_t* self){
    if (strcmp(self->funcion, CESAR) == 0){
        return cesar_destruir(self->tipo_de_encriptador);
    } else if (strcmp(self->funcion, VIGENERE) == 0){
        return vigenere_destruir(self->tipo_de_encriptador);
    } else if (strcmp(self->funcion, RC4) == 0){
        return rc4_destruir(self->tipo_de_encriptador);
    } else {
        return ERROR;
    }
}

int encriptador_destruir(encriptador_t* self){
    return destruir_tipo_de_encriptador(self);
}
