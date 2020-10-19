#include  <stdio.h>
#include <string.h>
#include "common_socket.h"
#include "common_encriptadores.h"
#include "client_lector.h"


#define MENSAJE_TAMANIO 150
#define TAMANIO_MAXIMO 200
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"
#define EXITO 0



static void mandar_mensaje(const char* mensaje,
                           int tamanio_mensaje,
                           void* callback_ctx){
    socket_t* socket = callback_ctx;
    socket_enviar(socket, mensaje, tamanio_mensaje);
}

static void encriptar_mensaje(void* callback_2, const char* mensaje,
                              int cant_leidos){
    encriptador_t* encriptador = callback_2;
    encriptador_encriptar(encriptador, (unsigned char*)mensaje, cant_leidos);
}
void inicializar_informacion(char* argv[], char host[TAMANIO_MAXIMO],
                             char service[TAMANIO_MAXIMO],
                             char* funcion[TAMANIO_MAXIMO],
                             char key[TAMANIO_MAXIMO]){
    strncpy(host,argv[1], TAMANIO_MAXIMO);
    const char* key_entrada = (argv[4] + 6);
    strncpy(key, key_entrada, TAMANIO_MAXIMO);
    const char* funcion_entrada = (argv[3] + 9);
    strncpy(funcion, funcion_entrada, TAMANIO_MAXIMO);
}
void verificar_funcion(encriptador_t* encriptador, char* key, char* funcion,
                       cesar_t* cesar, vigenere_t* vigenere, rc4_t* rc4){
    if (strcmp(funcion, CESAR)==0){
        cesar_inicializar(cesar, key);
        encriptador_inicializar(encriptador, funcion, (void*)cesar);
    } else if( strcmp(funcion, VIGENERE)==0){
        vigenere_inicializar(vigenere, key);
        return encriptador_inicializar(encriptador, funcion, (void*)vigenere);
    } else if (strcmp(funcion, RC4) == 0){
        rc4_inicializar(rc4,key);
        return encriptador_inicializar(encriptador, funcion, (void*)rc4);
    } else {
        printf(" no existe esa funcion");
    }
}

int main(int argc, char *argv[]){
    char host[TAMANIO_MAXIMO];
    //const char* key_entrada = (argv[4] + 6);
    //strncpy(host,argv[1], TAMANIO_MAXIMO);
    char service[TAMANIO_MAXIMO];
    //strncpy(service, argv[2], TAMANIO_MAXIMO);
    //strncpy(key, key_entrada, TAMANIO_MAXIMO);
    char funcion[TAMANIO_MAXIMO];
    socket_t socket;
    encriptador_t encriptador;
    lector_t lector;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    inicializar_informacion(argv, host, service, funcion, key);
    verificar_funcion(&encriptador, key, funcion, &cesar, &vigenere, &rc4);

    lector_inicializar(&lector, NULL);
    socket_inicializar(&socket);
    if (socket_conectar(&socket, host, service) == EXITO){;
        lector_iterar(&lector, mandar_mensaje, encriptar_mensaje, &socket,
                      &encriptador);
    }
    lector_destruir(&lector);
    socket_destruir(&socket);
    return 0;
}
