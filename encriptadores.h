#ifndef _ENCRIPTADORES_H
#define _ENCRIPTADORES_H


int cifrado_cesar(unsigned char* mensaje, int key);
int descifrar_cesar(unsigned char* mensaje, int key);
int cesar(unsigned char* mensaje, int key);
int cifrado_vigenere(unsigned char* mensaje, char* key);
int descrifrado_vigenere(unsigned char* mensaje, char* key);
int cifrado_rc4(unsigned char* mensaje, unsigned char* key);


#endif
