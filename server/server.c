#include "socket.h"
#include <stdio.h>
#include <string.h>

#define TAMANIO_MAXIMO 150



int main(int argc, char *argv[]){

    char service[TAMANIO_MAXIMO];
    strncpy(service, argv[1], TAMANIO_MAXIMO);
    char key[TAMANIO_MAXIMO];
    strncpy(key, argv[3], TAMANIO_MAXIMO);
    char* funcion = (argv[2] + 9);


    //file_lector_inicializar(&file_lector, nombre_archivo);
    socket_t socket;
    int verificacion = socket_bine_and_listen(&socket, NULL, service);
    //int verificacion = socket_conectar(&socket, "localhost", "7777");
    printf("hizo bine and listen : %i\n", verificacion);
    int pepe = socket_conectar(&socket, "127.0.0.1", "8080");
    printf(" pude conectar: %i\n", pepe);

    //file_lector_iterar(&file_lector, mandar_mensaje, &socket);
    //socket_destruir(&socket);
    //file_lector_destruir(&file_lector);
    socket_destruir(&socket);


}
