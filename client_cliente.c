#include "client_cliente.h"
#define MENSAJE_TAMANIO 150
#define TAMANIO_MAXIMO 200
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"
#define EXITO 0
#define ERROR 1
#define ERROR_FUNCION "No existe esa funcion, pruebe con cesar, vigenere o rc4"
#define PARCEO_KEY 6
#define PARCEO_FUNCION 9

/*
  * esta funcion se encarga de parcear e inicializar los corresponientes
  * argumentos, dejandolos ya cargados.
*/
static void inicializar_informacion(char* argv[], char host[TAMANIO_MAXIMO],
                             char service[TAMANIO_MAXIMO],
                             char funcion[TAMANIO_MAXIMO],
                             char key[TAMANIO_MAXIMO]){
    strncpy(service, argv[2], TAMANIO_MAXIMO);
    strncpy(host, argv[1], TAMANIO_MAXIMO);
    const char* key_entrada = (argv[4] + PARCEO_KEY);
    strncpy(key, key_entrada, TAMANIO_MAXIMO);
    const char* funcion_entrada = (argv[3] + PARCEO_FUNCION);
    strncpy(funcion, funcion_entrada, TAMANIO_MAXIMO);
}
/*
  * Esta funcion se encarga de verificar el metodo por el cual se desea
  * encriptar y asi poder crear al correspondiente encriptador.
  * Se devolvera exito si se pude verificar el metodo y crear el encriptador
  * generico, o error si no se la encontro
*/
static int verificar_funcion(encriptador_t* encriptador, char* key,
                            char* funcion, cesar_t* cesar, vigenere_t* vigenere,
                            rc4_t* rc4) {
    if (strcmp(funcion, CESAR) == 0){
        cesar_inicializar(cesar, key);
        encriptador_inicializar(encriptador, funcion, (void*)cesar);
        return EXITO;
    } else if (strcmp(funcion, VIGENERE) == 0){
        vigenere_inicializar(vigenere, key);
        encriptador_inicializar(encriptador, funcion, (void*)vigenere);
        return EXITO;
    } else if (strcmp(funcion, RC4) == 0){
        rc4_inicializar(rc4,key);
        encriptador_inicializar(encriptador, funcion, (void*)rc4);
        return EXITO;
    } else {
        printf("%s", ERROR_FUNCION);
        return ERROR;
    }
}
/*
  * esta funcion se encarga de mandar el mensaje que le llega
  *
*/
static void mandar_mensaje(const char* mensaje,
                           int tamanio_mensaje,
                           void* callback_socket){
    socket_t* socket = callback_socket;
    socket_enviar(socket, mensaje, tamanio_mensaje);
}
/*
  * Esta funcion se encragra de encriptar el mensaje que le llega
*/
 static void encriptar_mensaje(void* callback_encriptador, const char* mensaje,
                              int cant_leidos) {
    encriptador_t* encriptador = callback_encriptador;
    encriptador_encriptar(encriptador, (unsigned char*)mensaje, cant_leidos);
}

int cliente_inicializar(cliente_t* self, char host[TAMANIO_MAXIMO],
                        char key[TAMANIO_MAXIMO], char service[TAMANIO_MAXIMO],
                        char funcion[TAMANIO_MAXIMO], char* argv[]){
    inicializar_informacion(argv, host, service, funcion, key);
    strncpy(self->key, key, TAMANIO_MAXIMO);
    strncpy(self->service,service, TAMANIO_MAXIMO);
    strncpy(self->host, host, TAMANIO_MAXIMO);
    strncpy(self->funcion, funcion, TAMANIO_MAXIMO);
    if (verificar_funcion(&self->encriptador, self->key, self->funcion,
                      &self->cesar, &self->vigenere, &self->rc4) != EXITO){
          return ERROR;
    }
    lector_inicializar(&self->lector, NULL);
    socket_inicializar(&self->socket);
    return EXITO;
}

int cliente_run(cliente_t* self) {
    if (socket_conectar(&self->socket, self->host, self->service) == EXITO){;
        lector_iterar(&self->lector, encriptar_mensaje, mandar_mensaje,
                      &self->encriptador, &self->socket);
    }
    return EXITO;
}

int cliente_destruir(cliente_t* self){
    socket_destruir(&self->socket);
    lector_destruir(&self->lector);
    encriptador_destruir(&self->encriptador);
    return EXITO;
}
