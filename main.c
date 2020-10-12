#include  <stdio.h>
#include <string.h>
#include "socket.h"
#include "encriptadores.h"

#define EXITO 0
#define ERROR 0
#define MENSAJE_TAMANIO 150
#define TAMANIO_MAXIMO 200

typedef struct file_lector {

      FILE* file;
} file_lector_t;

typedef void (*file_lector_callback_t)(const char* mensaje, int tamanio_mensaje, void* callback_ctx);

int file_lector_inicializar(file_lector_t* self, const char* file_nombre){

    if(file_nombre !=NULL){
        self->file = fopen(file_nombre, "rb");
    }
    if(self->file == NULL){
      return ERROR;
    }
    return EXITO;
}



int file_lector_iterar(file_lector_t* self, file_lector_callback_t callback, void* callback_ctx) {

    char mensaje[MENSAJE_TAMANIO];
    while(!feof(self->file)){
      size_t cant_leidos = fread(mensaje, 1, MENSAJE_TAMANIO, self->file);
      callback(mensaje, cant_leidos, callback_ctx);
    }
    return EXITO;

}

int file_lector_destruir(file_lector_t* self){

    if (self->file != NULL){
        fclose(self->file);
    }
    return EXITO;
}

static void mandar_mensaje(const char* mensaje, int tamanio_mensaje, void* callback_ctx){

    socket_t* socket = callback_ctx;
    socket_enviar(socket, mensaje, tamanio_mensaje);

}


int main(int argc, char *argv[]){

    char nombre_archivo[TAMANIO_MAXIMO];
    strncpy(nombre_archivo,argv[4], TAMANIO_MAXIMO);
    char* funcion = (argv[2] + 9);
    file_lector_t file_lector;
    file_lector_inicializar(&file_lector, nombre_archivo);

    socket_t socket;
    socket_inicializar(&socket);
    socket_conectar(&socket, "local host", "7777");

    file_lector_iterar(&file_lector, mandar_mensaje, &socket);
    socket_destruir(&socket);
    file_lector_destruir(&file_lector);


}
