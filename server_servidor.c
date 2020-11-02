#include "server_servidor.h"
#include <stdio.h>
#include <stdbool.h>
#define TAMANIO_VECTOR 65
#define CESAR "cesar"
#define VIGENERE "vigenere"
#define RC4 "rc4"
#define ERROR 1
#define EXITO 0
#define ERROR_FUNCION "No existe esa funcion, pruebe con cesar, vigenere o rc4"

/*
  * esta funcion se encarga de parcear e inicializar los corresponientes
  * argumentos, dejandolos ya cargados.
*/
static void inicializar_informacion(char* argv[], char service[TAMANIO_MAXIMO],
                             char funcion[TAMANIO_MAXIMO],
                             char key[TAMANIO_MAXIMO]){
    strncpy(service, argv[1], TAMANIO_MAXIMO);
    const char *key_ingresada = (argv[3] + 6);
    strncpy(key, key_ingresada, TAMANIO_MAXIMO);
    const char* funcion_ingresada = (argv[2] + 9);
    strncpy(funcion, funcion_ingresada, TAMANIO_MAXIMO);
}
/*
  * Esta funcion se encarga de verificar el metodo por el cual se desea
  * encriptar y asi poder crear al correspondiente encriptador.
  * Se devolvera exito si se pude verificar el metodo y crear el encriptador
  * generico, o error si no se la encontro
*/
static int verificar_funcion(encriptador_t* encriptador, char* key,
                              char* funcion, cesar_t* cesar,
                              vigenere_t* vigenere, rc4_t* rc4){
    if (strcmp(funcion, CESAR)==0){
        cesar_inicializar(cesar, key);
        encriptador_inicializar(encriptador, funcion, (void*)cesar);
        return EXITO;
    } else if (strcmp(funcion, VIGENERE)==0){
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
/* Esta funcion se encarga de probcesar los bytes que se recibieron del
  * socket para luego estos desencriptarlos e imprimirlos por pantalla
  * si hubo un error se devolvera error sino exito
*/
static int procesar_desencriptacion(socket_t* peer, encriptador_t* encriptador){
    char respuesta[TAMANIO_VECTOR];
    bool hubo_un_error = false;
    bool finalice = false;
    while (!hubo_un_error && !finalice){
        int bytes_recibidos = socket_recibir(peer, respuesta, TAMANIO_VECTOR);
        if (bytes_recibidos == -1){
              hubo_un_error = true;
        } else if (bytes_recibidos == 0){
              finalice = true;
        } else {
              encriptador_desencriptar(encriptador, (unsigned char*)respuesta,
                                        bytes_recibidos);
              respuesta[bytes_recibidos] = '\0';
              fwrite(respuesta, 1, bytes_recibidos, stdout);
        }
    }
    if (hubo_un_error){
        return ERROR;
    }
    return EXITO;
}

int servidor_inicializar(servidor_t* self, char service[TAMANIO_MAXIMO],
                        char funcion[TAMANIO_MAXIMO], char key[TAMANIO_MAXIMO],
                        char* argv[]){
      inicializar_informacion(argv, service, funcion , key);
      strncpy(self->key, key, TAMANIO_MAXIMO);
      strncpy(self->service,service, TAMANIO_MAXIMO);
      strncpy(self->funcion, funcion, TAMANIO_MAXIMO);
      if (verificar_funcion(&self->encriptador, self->key, self->funcion,
                          &self->cesar, &self->vigenere, &self->rc4) != EXITO){
            return ERROR;
      }
      socket_inicializar(&self->socket);
      socket_inicializar(&self->peer);
      return EXITO;
}

int servidor_run(servidor_t* self){
    if (socket_bine_and_listen(&self->socket, NULL, self->service) == ERROR){
        return ERROR;
    }
    if (socket_acceptar(&self->socket, &self->peer) == EXITO){;
            return procesar_desencriptacion(&self->peer, &self->encriptador);
    }
    return ERROR;
}

int servidor_destruir(servidor_t* self){
    socket_destruir(&self->peer);
    socket_destruir(&self->socket);
    encriptador_destruir(&self->encriptador);
    return EXITO;
}
