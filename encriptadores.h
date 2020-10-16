#ifndef _ENCRIPTADORES_H
#define _ENCRIPTADORES_H




typedef struct encriptador {
      void* key;
      int(*funcion)(unsigned char* mensaje, void* key);
} encriptador_t;


int encriptador_inicializar(encriptador_t *self, void* key, int (*funcion)(unsigned char*, void*));
int encriptador_encriptar(encriptador_t *self, unsigned char* mensaje);
int encriptador_desencriptar(encriptador_t* self, unsigned char* mensaje);

int cifrado_cesar(unsigned char* mensaje, void* key);
int descifrar_cesar(unsigned char* mensaje, void* key);
int cifrado_vigenere(unsigned char* mensaje, void* key);
int descrifrado_vigenere(unsigned char* mensaje, void* key);
int cifrado_rc4(unsigned char* mensaje, void* key);

int encriptador_destruir(encriptador_t *self);


#endif
