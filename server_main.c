#include "common_socket.h"
#include "common_encriptadores.h"
#include "common_cesar.h"
#include "common_rc4.h"
#include "common_vigenere.h"
#include <stdio.h>
#include <string.h>


#define TAMANIO_MAXIMO 100
#define TAMANIO_VECTOR 2
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"



static void desencriptar_mensaje(void* callback_2, const char* mensaje,
                                 int tamanio){
    encriptador_t* encriptador = callback_2;
    encriptador_desencriptar(encriptador, (unsigned char*)mensaje, tamanio);
}

void inicializar_informacion(char* argv[], char service[TAMANIO_MAXIMO],
                             char funcion[TAMANIO_MAXIMO],
                             char key[TAMANIO_MAXIMO]){
    strncpy(service, argv[1], TAMANIO_MAXIMO);
    const char *key_ingresada = (argv[3] + 6);
    strncpy(key, key_ingresada, TAMANIO_MAXIMO);
    const char* funcion_ingresada = (argv[2] + 9);
    strncpy(funcion, funcion_ingresada, TAMANIO_MAXIMO);
}

void verificar_funcion(encriptador_t* encriptador, char* key, char* funcion,
                        cesar_t* cesar, vigenere_t* vigenere, rc4_t* rc4){
    if (strcmp(funcion, CESAR)==0){
        cesar_inicializar(cesar, key);
        encriptador_inicializar(encriptador, funcion, (void*)cesar);
    } else if (strcmp(funcion, VIGENERE)==0){
        vigenere_inicializar(vigenere, key);
        encriptador_inicializar(encriptador, funcion, (void*)vigenere);
    } else if (strcmp(funcion, RC4) == 0){
        rc4_inicializar(rc4,key);
        encriptador_inicializar(encriptador, funcion, (void*)rc4);
    } else {
        printf(" no existe esa funcion");
    }
}

int main(int argc, char *argv[]){
    char service[TAMANIO_MAXIMO];

    char key[TAMANIO_MAXIMO];
    char* funcion;
    inicializar_informacion(argv, service, funcion , key);
    encriptador_t encriptador;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    socket_t socket;
    socket_t peer;
    verificar_funcion(&encriptador, key, funcion, &cesar, &vigenere, &rc4);
    socket_inicializar(&socket);
    socket_inicializar(&peer);
    socket_bine_and_listen(&socket, NULL, service);
    socket_acceptar(&socket,&peer);
    char respuesta[TAMANIO_VECTOR] = "";
    socket_recibir(&peer,respuesta,TAMANIO_VECTOR,desencriptar_mensaje,
                   &encriptador);
    socket_destruir(&peer);
    socket_destruir(&socket);

    return 0;
}
