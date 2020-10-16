#include "common_socket.h"
#include "common_encriptadores.h"
#include <stdio.h>
#include <string.h>


#define TAMANIO_MAXIMO 65
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"


void verificar_encriptador(encriptador_t* encriptador, const char* encriptador_elegido, char* key){
    //printf("key:%i\n", *(int*)key);

    if (strcmp(encriptador_elegido, CESAR) == 0){
        encriptador_inicializar(encriptador, key, descifrar_cesar);
    }else if (strcmp(encriptador_elegido, VIGENERE) == 0){
        encriptador_inicializar(encriptador, key, descrifrado_vigenere);
    }else if (strcmp(encriptador_elegido, RC4) == 0){
        encriptador_inicializar(encriptador, key, cifrado_rc4);
    }

}
static void desencriptar_mensaje(void* callback_2, const char* mensaje){
    encriptador_t* encriptador = callback_2;
    encriptador_desencriptar(encriptador, (unsigned char*)mensaje);
}

int main(int argc, char *argv[]){

    char service[TAMANIO_MAXIMO];
    strncpy(service, argv[1], TAMANIO_MAXIMO);
    char key[TAMANIO_MAXIMO];
    const char *key_ingresada = (argv[3] + 6);
    strncpy(key, key_ingresada, TAMANIO_MAXIMO);

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
    socket_recibir(&peer, respuesta, TAMANIO_MAXIMO, desencriptar_mensaje, &encriptador);
    //encriptador_desencriptar(&encriptador, (unsigned char*)respuesta);

    socket_destruir(&peer);
    socket_destruir(&socket);


}
