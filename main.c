#include  <stdio.h>

#define EXITO 0;

typedef struct file_lector {

      FILE* file;
} file_lector_t;

int file_lector_inicializar(file_lector_t* self, const char* file_nombre){

    self->file = file_nombre ? fopen(file_nombre, "rb") : stdin;
    return EXITO;
}



int file_lector_destruir(file_lector_t* self){

    if (self->file != stdin){
        fclose(self->file);
    }
    return EXITO;
}

int cifrado_cesar(unsigned char* mensaje, int key){

    return cesar(mensaje, key);
}

int descifrar_cesar(unsigned char* mensaje, int key){
    return cesar(mensaje, -key);
}

int cesar(unsigned char* mensaje, int key){
    int i = 0;
    while (mensaje[i]!= '\0'){
      mensaje[i] = (mensaje[i] + key);
      printf( "|%i|", mensaje[i]);
      i++;
    }
    return EXITO;
}

int cifrado_vigenere(unsigned char* mensaje, char* key){

    int i = 0;
    int j = 0;
    while (mensaje[i] != '\0'){
      if (key[j] == '\0'){
          j = 0;
      }
      mensaje[i] = (mensaje[i] + key[j]);
      printf( "|%i|", mensaje[i]);
      i++;
      j++;
  }
  return EXITO;

}

int descrifrado_vigenere(unsigned char* mensaje, char* key){
    int i = 0;
    int j = 0;
    while (mensaje[i] != '\0'){
        if (key[j] == '\0'){
            j = 0;
        }
        mensaje[i] = (mensaje[i] - key[j]);
        printf( "|%i|", mensaje[i]);
        i++;
        j++;
    }
    return EXITO;
}

void swap(unsigned char *s_box, unsigned int i, unsigned int j) {
    unsigned char auz = s_box[i];
    s_box[i] = s_box[j];
    s_box[j] = aux;
}

unsigned char rc4_output(unsigned char* s_box) {
    int i = j = 0;
    i = (i + 1) & 255;
    j = (j + s_box[i]);

    swap(s_box, i, j);

    return s_box[(s_box[i] + s_box[j]) & 255];
}

int cifrado_rc4(unsigned char* mensaje, unsigned char* key){
    unsigned char* s_box;
    int j = 0;

    for (i = 0; i < 256; i++){
        s_box[i] = i;
    }
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % strlen(key)] + s_box[i]);
        swap(s_box, i, j);
    }
    rc4_output(s_box);
}


int main(int argc, char *argv[]){

    char cadena[] = "hola";
    char cadena2[] = "Secret message";
    int key = 3;
    char key2[] = "SecureKey";
    cifrado_cesar((unsigned char*)cadena, key);
    printf("cadena: %s\n", cadena);
    cifrado_vigenere((unsigned char*)cadena2, key2);
    printf("cadena: %s\n", cadena2);
    //file_lector_t file_lector;
    //file_lector_t file_lector_inicializar(&file_lector, NULL);
}
