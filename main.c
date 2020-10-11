#include  <stdio.h>

typedef struct file_lector {

      File* file;
} file_lector_t;

int file_lector_inicializar(file_lector* self, const char* file_nombre){

    self->file = file_nombre ? fopen(file_nombre, "rb") : stdin;
    return 0;
}

int file_lector_leer(file_lector* self, )

int file_lector_destruir(file_lector* self){

    if (self->file != stdin){
        fclose(self->file);
    }
    return 0;
}




int main(int arg char const *argv[]){

    file_lector_t file_lector;
    file_lector_t file_lector_inicializar(&file_lector, NULL);
}
