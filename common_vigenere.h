#ifndef _COMMON_VIGENERE_H
#define _COMMON_VIGENERE_H

typedef struct vigenere {
      char* key;
      int posicion_key;
} vigenere_t;



int vigenere_inicializar(vigenere_t* self, char* key);

int vigenere_cifrado(vigenere_t* self, unsigned char* mensaje, int tamanio, int formato);

int vigenere_destruir(vigenere_t* self);


#endif
