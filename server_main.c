#include "server_servidor.h"
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include "common_encriptadores.h"
#include <stdio.h>
#include <string.h>

#define CANTIDAD_ARGUMENTOS 4
#define ERROR_ARGUMENTOS "La cantidad de argumentos ingresados no es valida,"
#define CANTIDAD_CORRECTA "deben ser 4\n"
#define EJEMPLO_ARGC "./server 8080 --metodo=cesar --key=4\n"




 static void mensaje_error_argumentos(){
    printf("%s", ERROR_ARGUMENTOS);
    printf("%s", CANTIDAD_CORRECTA);
    printf("%s", EJEMPLO_ARGC);
}

int main(int argc, char *argv[]){
    if (argc != CANTIDAD_ARGUMENTOS){
        mensaje_error_argumentos();
        return 0;
    }
    char service[TAMANIO_MAXIMO];
    char key[TAMANIO_MAXIMO];
    char funcion[TAMANIO_MAXIMO];
    servidor_t servidor;
    servidor_inicializar(&servidor, service, funcion, key, argv);
    servidor_run(&servidor);
    servidor_destruir(&servidor);

    return 0;
}
