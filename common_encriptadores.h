#ifndef _COMMON_ENCRIPTADORES_H
#define _COMMON_ENCRIPTADORES_H




typedef struct encriptador {
      char* key;
      int(*funcion)(unsigned char* mensaje, char* key);
} encriptador_t;


int encriptador_inicializar(encriptador_t *self, char* key, int (*funcion)(unsigned char*, char*));
int encriptador_encriptar(encriptador_t *self, unsigned char* mensaje);
int encriptador_desencriptar(encriptador_t* self, unsigned char* mensaje);

int cifrado_cesar(unsigned char* mensaje, char* key);
int descifrar_cesar(unsigned char* mensaje, char* key);
int cifrado_vigenere(unsigned char* mensaje, char* key);
int descrifrado_vigenere(unsigned char* mensaje, char* key);
int cifrado_rc4(unsigned char* mensaje, char* key);

int encriptador_destruir(encriptador_t *self);


#endif
