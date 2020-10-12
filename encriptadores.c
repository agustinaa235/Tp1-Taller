#include "encriptadores.h"
#include <stdio.h>
#include <string.h>


#define EXITO 0

int cifrado_cesar(unsigned char* mensaje, int key){

    return cesar(mensaje, key);
}

int descifrar_cesar(unsigned char* mensaje, int key){
    return cesar(mensaje, -key);
}

int cesar(unsigned char* mensaje, int key){
    int i = 0;
    while (mensaje[i]!= '\0'){
      mensaje[i] = (mensaje[i] + key);
      printf( "|%i|", mensaje[i]);
      i++;
    }
    return EXITO;
}

int cifrado_vigenere(unsigned char* mensaje, char* key){

    int i = 0;
    int j = 0;
    while (mensaje[i] != '\0'){
      if (key[j] == '\0'){
          j = 0;
      }
      mensaje[i] = (mensaje[i] + key[j]);
      printf( "|%i|", mensaje[i]);
      i++;
      j++;
  }
  return EXITO;

}

int descrifrado_vigenere(unsigned char* mensaje, char* key){
    int i = 0;
    int j = 0;
    while (mensaje[i] != '\0'){
        if (key[j] == '\0'){
            j = 0;
        }
        mensaje[i] = (mensaje[i] - key[j]);
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

int cifrado_rc4(unsigned char* mensaje, unsigned char* key){
    unsigned char* s_box;
    int j = 0;

    for (int i = 0; i < 256; i++){
        s_box[i] = i;
    }
    for (int i = j = 0; i < 256; i++) {
        j = (j + key[i % strlen(key)] + s_box[i]);
        swap(s_box, i, j);
    }
    return *mensaje^rc4_output(s_box);
}
