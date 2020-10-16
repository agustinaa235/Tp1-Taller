#include  <stdio.h>
#include <string.h>
#include "socket.h"
#include "encriptadores.h"
#include "file_reader.h"

#define EXITO 0
#define ERROR 0
#define MENSAJE_TAMANIO 150
#define TAMANIO_MAXIMO 200
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"



static void mandar_mensaje(const char* mensaje, int tamanio_mensaje, void* callback_ctx){

    socket_t* socket = callback_ctx;
    socket_enviar(socket, mensaje, tamanio_mensaje);

}

void verificar_encriptador(encriptador_t* encriptador, const char* encriptador_elegido,void* key){
    //printf("key:%i\n", *(int*)key);

    if (strcmp(encriptador_elegido, CESAR) == 0){
        encriptador_inicializar(encriptador, key, cifrado_cesar);
    }else if (strcmp(encriptador_elegido, VIGENERE) == 0){
        encriptador_inicializar(encriptador, key, cifrado_vigenere);
    }else if (strcmp(encriptador_elegido, RC4) == 0){
        encriptador_inicializar(encriptador, key, cifrado_rc4);
    }

}
static void encriptar_mensaje(void* callback_2, const char* mensaje){
    encriptador_t* encriptador = callback_2;
    encriptador_encriptar(encriptador, (unsigned char*)mensaje);
}


//client
int main(int argc, char *argv[]){

    char nombre_archivo[TAMANIO_MAXIMO];
    char host[TAMANIO_MAXIMO];
    const char* key_entrada = (argv[4] + 6);
    strncpy(host,argv[1], TAMANIO_MAXIMO);
    char service[TAMANIO_MAXIMO];
    strncpy(service, argv[2], TAMANIO_MAXIMO);
    char key[TAMANIO_MAXIMO];
    strncpy(key, key_entrada, TAMANIO_MAXIMO);
    strncpy(nombre_archivo,(argv[5]), TAMANIO_MAXIMO);
    const char* funcion = (argv[3] + 9);
    encriptador_t encriptador;
    verificar_encriptador(&encriptador, funcion, key);
    lector_t lector;
    lector_inicializar(&lector, nombre_archivo);


    socket_t socket;
    socket_inicializar(&socket);
    socket_conectar(&socket, host, service);
    lector_iterar(&lector, mandar_mensaje, encriptar_mensaje, &socket, &encriptador);
    socket_destruir(&socket);


    lector_destruir(&lector);
/*
    char mensaje[TAMANIO_MAXIMO] = "Pan";
    int key = 5;
    //cifrado_cesar(mensaje, (void*)key);
    printf("mensaje prueba cesar: %s", mensaje);*/
}
