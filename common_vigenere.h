#ifndef _COMMON_VIGENERE_H
#define _COMMON_VIGENERE_H

typedef struct vigenere {
      char* key;
      int pos_key;
} vigenere_t;



/*
  * inicializar la estructa rc4 dejando la valida para usa
*/
int vigenere_inicializar(vigenere_t* self, char* key);
/*
  * cifrara el mensaje que le llegue con el correspondiente formato
  * este mensaje debe ser valido
*/
int vigenere_cifrado(vigenere_t* self, unsigned char* mensaje, int tamanio,
                     int formato);
/*
 * destruira la estructura
*/
int vigenere_destruir(vigenere_t* self);

#endif
