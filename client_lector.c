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
                  lector_callback_t callback,
                  lector_callback2_t callback2,
                  void* callback_ctx,
                  void* callback_2) {
    bool hubo_un_error = false;
    char mensaje[MENSAJE_TAMANIO] = "";
    while (!feof(self->file) && !hubo_un_error){
        size_t cant_leidos = fread(mensaje, 1, MENSAJE_TAMANIO, self->file);
        if (cant_leidos > 0){
            callback2(callback_2, mensaje, cant_leidos);
            callback(mensaje, cant_leidos, callback_ctx);
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
