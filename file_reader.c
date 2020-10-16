#include "file_reader.h"

#define ERROR 1
#define EXITO 0
#define MENSAJE_TAMANIO 150

int lector_inicializar(lector_t* self, const char* file_nombre){

    if(file_nombre !=NULL){
        self->file = fopen(file_nombre, "rb");
    }
    if(self->file == NULL){
      return ERROR;
    }
    return EXITO;
}



int lector_iterar(lector_t* self, lector_callback_t callback, lector_callback2_t callback2, void* callback_ctx, void* callback_2) {

    char mensaje[MENSAJE_TAMANIO] = "";
    while(!feof(self->file)){
      size_t cant_leidos = fread(mensaje, 1, MENSAJE_TAMANIO, self->file);
      printf("mensaje leido del archivo: %s\n\n", mensaje);
      callback2(callback_2, mensaje);
      callback(mensaje, cant_leidos, callback_ctx);
    }
    return EXITO;

}

int lector_destruir(lector_t* self){

    if (self->file != NULL){
        fclose(self->file);
    }
    return EXITO;
}
