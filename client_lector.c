#include "client_lector.h"
#include <stdbool.h>
#define ERROR 1
#define EXITO 0
#define MENSAJE_TAMANIO 64

int lector_inicializar(lector_t* self, const char* file_nombre){
    if (file_nombre){
        self->file = fopen(file_nombre, "rb");
        if (!self->file){
            return ERROR;
        }
    } else {
      self->file = stdin;
    }
    return EXITO;
}

int lector_iterar(lector_t* self,
                  lector_encriptacion_t encriptacion,
                  lector_enviar_mensaje_t enviar,
                  void* callback_encriptador,
                  void* callback_enviador) {
    bool hubo_un_error = false;
    char mensaje[MENSAJE_TAMANIO] = "";
    while (!feof(self->file) && !hubo_un_error){
        size_t cant_leidos = fread(mensaje, 1, MENSAJE_TAMANIO, self->file);
        if (cant_leidos > 0){
            encriptacion(callback_encriptador, mensaje, cant_leidos);
            enviar(mensaje, cant_leidos, callback_enviador);
        } else {
            hubo_un_error = true;
        }
    }
    if (hubo_un_error){
        return ERROR;
    }
    return EXITO;
}

int lector_destruir(lector_t* self){
    if (self->file != NULL){
        fclose(self->file);
    }
    return EXITO;
}
