#include  <stdio.h>
#include <string.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include "common_socket.h"
#include "common_encriptadores.h"
#include "client_lector.h"

#define MENSAJE_TAMANIO 150
#define TAMANIO_MAXIMO 200
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"
#define EXITO 0
#define ERROR 1
#define CANTIDAD_ARGUMENTOS 5



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

static void inicializar_informacion(char* argv[], char host[TAMANIO_MAXIMO],
                             char service[TAMANIO_MAXIMO],
                             char funcion[TAMANIO_MAXIMO],
                             char key[TAMANIO_MAXIMO]){
    strncpy(service, argv[2], TAMANIO_MAXIMO);
    strncpy(host,argv[1], TAMANIO_MAXIMO);
    const char* key_entrada = (argv[4] + 6);
    strncpy(key, key_entrada, TAMANIO_MAXIMO);
    const char* funcion_entrada = (argv[3] + 9);
    strncpy(funcion, funcion_entrada, TAMANIO_MAXIMO);
}

int verificar_funcion(encriptador_t* encriptador, char* key, char* funcion,
                       cesar_t* cesar, vigenere_t* vigenere, rc4_t* rc4){
    if (strcmp(funcion, CESAR) == 0){
        cesar_inicializar(cesar, key);
        encriptador_inicializar(encriptador, funcion, (void*)cesar);
        return EXITO;
    } else if (strcmp(funcion, VIGENERE) == 0){
        vigenere_inicializar(vigenere, key);
        encriptador_inicializar(encriptador, funcion, (void*)vigenere);
        return EXITO;
    } else if (strcmp(funcion, RC4) == 0){
        rc4_inicializar(rc4,key);
        encriptador_inicializar(encriptador, funcion, (void*)rc4);
        return EXITO;
    } else {
        printf(" no existe esa funcion, pruebe con cesar, vigenere o rc4\n");
        return ERROR;
    }
}

static void mensaje_error_argumentos(){
    printf(" La cantidad de argumentos ingresados no es valida, deben ser 5\n");
    printf(" Ejemplo de argumentos ./client 127.0.0.1 8080 --metodo=cesar");
    printf(" --key-4 < client_archivo\n");
}

int main(int argc, char *argv[]){
    if (argc != CANTIDAD_ARGUMENTOS){
        mensaje_error_argumentos();
        return 0;
    }
    char host[TAMANIO_MAXIMO];
    char key[TAMANIO_MAXIMO];
    char service[TAMANIO_MAXIMO];
    char funcion[TAMANIO_MAXIMO];
    socket_t socket;
    encriptador_t encriptador;
    lector_t lector;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    inicializar_informacion(argv, host, service, funcion, key);
    if (verificar_funcion(&encriptador, key, funcion, &cesar, &vigenere,
                          &rc4) == ERROR){
        return 0;
    }
    lector_inicializar(&lector, NULL);
    socket_inicializar(&socket);
    if (socket_conectar(&socket, host, service) == EXITO){;
        lector_iterar(&lector, mandar_mensaje, encriptar_mensaje, &socket,
                      &encriptador);
    }
    socket_destruir(&socket);
    lector_destruir(&lector);
    encriptador_destruir(&encriptador);
    return 0;
}
