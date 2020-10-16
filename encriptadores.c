#include "encriptadores.h"
#include <stdio.h>
#include <string.h>


#define EXITO 0


int encriptador_inicializar(encriptador_t *self, void* key, int (*funcion)(unsigned char*, void*)){

    self->key = key;
    self->funcion = funcion;
    return EXITO;
}


int cesar(unsigned char* mensaje, int key){

    int i = 0;
    while (mensaje[i]!= '\0'){
      mensaje[i] = (mensaje[i] + 5);
      printf( "|%i|", mensaje[i]);
      i++;
    }
    printf(" key en cesar: %i\n", key);
    printf("\nmensaje cifrado en cesar: %s\n", mensaje);
    return EXITO;
}

int cifrado_cesar(unsigned char* mensaje, void* key){
    int key_aux = 0;
    key_aux = *(int*)key;
    return cesar(mensaje, key_aux);
}

int descifrar_cesar(unsigned char* mensaje, void* key){
    int key_aux = 0;
    key_aux = *(int*)key;
    return cesar(mensaje, -(key_aux));
}


int cifrado_vigenere(unsigned char* mensaje, void* key){

    int i = 0;
    int j = 0;
    char* key_aux = key;
    while (mensaje[i] != '\0'){
      if (key_aux[j] == '\0'){
          j = 0;
      }
      mensaje[i] = (mensaje[i] + key_aux[j]);
      printf( "|%i|", mensaje[i]);
      i++;
      j++;
  }
  return EXITO;

}

int descrifrado_vigenere(unsigned char* mensaje, void* key){
    int i = 0;
    int j = 0;
    char* key_aux = key;
    while (mensaje[i] != '\0'){
        if (key_aux[j] == '\0'){
            j = 0;
        }
        mensaje[i] = (mensaje[i] - key_aux[j]);
        printf( "|%i|", mensaje[i]);
        i++;
        j++;
    }
    return EXITO;
}

void swap(unsigned char *s_box, unsigned int i, unsigned int j) {
    unsigned char aux = s_box[i];
    s_box[i] = s_box[j];
    s_box[j] = aux;
}

unsigned char rc4_output(unsigned char* s_box) {
    int i = 0;
    int j = 0;
    i = (i + 1) & 255;
    j = (j + s_box[i]);

    swap(s_box, i, j);

    return s_box[(s_box[i] + s_box[j]) & 255];
}

int cifrado_rc4(unsigned char* mensaje, void* key){
    unsigned char* s_box;
    int j = 0;
    char* key_aux = key;
    for (int i = 0; i < 256; i++){
        s_box[i] = i;
    }
    for (int i = j = 0; i < 256; i++) {
        j = (j + key_aux[i % strlen(key_aux)] + s_box[i]);
        swap(s_box, i, j);
    }
    return *mensaje^rc4_output(s_box);
}

int encriptador_encriptar(encriptador_t *self, unsigned char* mensaje){
      return self->funcion(mensaje,self->key);
}
int encriptador_desencriptar(encriptador_t* self, unsigned char* mensaje){
      return self->funcion(mensaje, self->key);
}
