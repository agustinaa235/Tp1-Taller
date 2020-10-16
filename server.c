#include "socket.h"
#include "encriptadores.h"
#include <stdio.h>
#include <string.h>


#define TAMANIO_MAXIMO 150
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"


void verificar_encriptador(encriptador_t* encriptador, const char* encriptador_elegido,void* key){
    //printf("key:%i\n", *(int*)key);

    if (strcmp(encriptador_elegido, CESAR) == 0){
        encriptador_inicializar(encriptador, key, descifrar_cesar);
    }else if (strcmp(encriptador_elegido, VIGENERE) == 0){
        encriptador_inicializar(encriptador, key, descrifrado_vigenere);
    }else if (strcmp(encriptador_elegido, RC4) == 0){
        encriptador_inicializar(encriptador, key, cifrado_rc4);
    }

}

int main(int argc, char *argv[]){

    char service[TAMANIO_MAXIMO];
    strncpy(service, argv[1], TAMANIO_MAXIMO);
    char key[TAMANIO_MAXIMO];
    const char *key_ingresada = (argv[3] + 6);
    strncpy(key, key_ingresada, TAMANIO_MAXIMO);
    strncpy(key, argv[3], TAMANIO_MAXIMO);
    char* funcion = (argv[2] + 9);

    encriptador_t encriptador;
    verificar_encriptador(&encriptador, funcion, key);
    socket_t socket;
    socket_t peer;
    socket_inicializar(&socket);
    socket_inicializar(&peer);
    socket_bine_and_listen(&socket, NULL, service);

    int aceptar = socket_acceptar(&socket,&peer);
    char respuesta[TAMANIO_MAXIMO] = "";
    socket_recibir(&peer, respuesta, TAMANIO_MAXIMO);
    encriptador_desencriptar(&encriptador, (unsigned char*)respuesta);
    printf("\nmensaje recibido: %s\n", respuesta);


    socket_destruir(&peer);
    socket_destruir(&socket);


}
