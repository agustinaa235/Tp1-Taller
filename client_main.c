#include "client_cliente.h"
#include "common_socket.h"
#include "common_encriptadores.h"
#include "client_lector.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include  <stdio.h>
#include <string.h>


#define TAMANIO_MAXIMO 200
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"
#define EXITO 0
#define ERROR 1
#define CANTIDAD_ARGUMENTOS 5
#define MENSAJE_TAMANIO 150
#define TAMANIO_MAXIMO 200
#define ERROR_ARGUMENTOS "La cantidad de argumentos ingresados no es valida"
#define LA_CANTIDAD " Estos deben ser 5\n"
#define EJEMPLO_ARGC "./client 127.0.0.1 8080 --metodo=cesar--key-4 < archivo"



static void mensaje_error_argumentos(){
    printf("%s", ERROR_ARGUMENTOS);
    printf("%s", LA_CANTIDAD);
    printf("%s", EJEMPLO_ARGC);
}

int main(int argc, char* argv[]){
    if (argc != CANTIDAD_ARGUMENTOS){
        mensaje_error_argumentos();
        return 0;
    }
    char host[TAMANIO_MAXIMO];
    char key[TAMANIO_MAXIMO];
    char service[TAMANIO_MAXIMO];
    char funcion[TAMANIO_MAXIMO];
    cliente_t cliente;
    cliente_inicializar(&cliente, host, key, service, funcion, argv);
    cliente_run(&cliente);
    cliente_destruir(&cliente);
    return 0;
}
