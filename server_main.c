#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include "common_encriptadores.h"
#include <stdio.h>
#include <string.h>


#define TAMANIO_MAXIMO 100
#define TAMANIO_VECTOR 64
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"
#define ERROR 1
#define EXITO 0
#define CANTIDAD_ARGUMENTOS 4


static void desencriptar_mensaje(void* callback_3, const char* mensaje,
                                 int tamanio){
    encriptador_t* encriptador = callback_3;
    encriptador_desencriptar(encriptador, (unsigned char*)mensaje, tamanio);
}

static void inicializar_informacion(char* argv[], char service[TAMANIO_MAXIMO],
                             char funcion[TAMANIO_MAXIMO],
                             char key[TAMANIO_MAXIMO]){
    strncpy(service, argv[1], TAMANIO_MAXIMO);
    const char *key_ingresada = (argv[3] + 6);
    strncpy(key, key_ingresada, TAMANIO_MAXIMO);
    const char* funcion_ingresada = (argv[2] + 9);
    strncpy(funcion, funcion_ingresada, TAMANIO_MAXIMO);
}

int verificar_funcion(encriptador_t* encriptador, char* key, char* funcion,
                        cesar_t* cesar, vigenere_t* vigenere, rc4_t* rc4){
    if (strcmp(funcion, CESAR)==0){
        cesar_inicializar(cesar, key);
        encriptador_inicializar(encriptador, funcion, (void*)cesar);
        return EXITO;
    } else if (strcmp(funcion, VIGENERE)==0){
        vigenere_inicializar(vigenere, key);
        encriptador_inicializar(encriptador, funcion, (void*)vigenere);
        return EXITO;
    } else if (strcmp(funcion, RC4) == 0){
        rc4_inicializar(rc4,key);
        encriptador_inicializar(encriptador, funcion, (void*)rc4);
        return EXITO;
    } else {
        printf(" no existe esa funcion);con cesar, vigenere o rc4, pruebe ");
        return ERROR;
    }
}
 static void mensaje_error_argumentos(){
    printf(" La cantidad de argumentos ingresados no es valida, deben ser 4\n");
    printf(" Ejemplo de argumentos ./server 8080 --metodo=cesar --key=4\n");
}

int main(int argc, char *argv[]){
    if (argc != CANTIDAD_ARGUMENTOS){
        mensaje_error_argumentos();
        return 0;
    }
    char service[TAMANIO_MAXIMO];
    char key[TAMANIO_MAXIMO];
    char funcion[TAMANIO_MAXIMO];
    char respuesta[TAMANIO_VECTOR];
    encriptador_t encriptador;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    socket_t socket;
    socket_t peer;
    inicializar_informacion(argv, service, funcion , key);
    if (verificar_funcion(&encriptador, key, funcion, &cesar, &vigenere,
                          &rc4) == ERROR){
        return 0;
    }
    socket_inicializar(&socket);
    socket_inicializar(&peer);
    socket_bine_and_listen(&socket, NULL, service);
    socket_acceptar(&socket,&peer);
    socket_recibir(&peer,respuesta,TAMANIO_VECTOR,desencriptar_mensaje,
                   &encriptador);

    socket_destruir(&peer);
    socket_destruir(&socket);
    encriptador_destruir(&encriptador);

    return 0;
}
