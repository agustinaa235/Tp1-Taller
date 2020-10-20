#ifndef _COMMON_CESAR_H
#define _COMMON_CESAR_H

typedef struct cesar {
      char* key;
} cesar_t;


/*
  * inicializara la estructura cesar dejandola valida para uso
*/
int cesar_inicializar(cesar_t* self, char* key);

/*
 *cifrara el mensaje que le llega por parametro, este debe llegar valido
 */
int cesar_cifrado(cesar_t* self, unsigned char* mensaje, int tamanio,
                  int formato);
/*
  * Se encarga de destruir la estructura cesar
*/  
int cesar_destruir(cesar_t* self);


#endif
