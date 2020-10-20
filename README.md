# Tp1

# Informacion Estudiante

Nombre: Agustina segura
Padron: 10422

# Intruccion

El tp consta de de dos programas ( un cliente y un servidor) en donde el cliente recibe mensajes de entrada estandar, luego estos mensajes son encriptados y envaidos al servidor donde este cuando los recibe los desencripta y los muestra por salida estandar. Los cifrados de este tp fueron: cesar, vigenere y rc4.


# Disenio del tp

El disenio consta de dos programas generales donde en uno se modela a un cliente y en el otro a un servidor, en la cual el cliente va a enviarle mensajes al servidor.
En el tp se decidio modelar los distintos tdas:

* socket

    Este tda es conocido por ambos programas ya que ambos lo necesitan. Por un lado el cliente lo utiliza para hacer un connect y enviar los mensajes con un send mientras que para el servido lo utiliza para hacer un bine and listes, un accept y para recibir los mensajes enviados por el cliente.

* lector

    Se modelo este tda para poder tenerlo sepadado del cliente y lograr una abstraccion. Este se encarga de leer los mensajes que recibie por entrada estandar.

* Encriptador

    Se modelo esta entidad generica de encriptador en la cual se guarda la referencia de la funcion correspiende que llega al programa por entrada estandar y luego en base a esa misma funcion se guarda un tipo de encriptador. Ese tda se encarga de encriptar y desencriptar en base al tipo de encriptador que se guardo cuando fue creado.

En el tp se usaron 3 tipos de cifrados distintos, en la cual fueron modelados en 3 tdas distintos. Esto fue porque cada uno para el tema del descrifrado necesitaban guaradarse distintas referencias que otro encriptador no necesitaba.

Este se encarga de hacer su cifrado. Tanto para la encriptacion como desencriptacion se utilizo una misma funcion que recibe un modo para saber com ser tratada si es modo = 1  se trata de encriptaccion y si modo = -1 se trata de desencriptacion.

* Cesar    

    Este tda solo necesitaba guardarse la referencia a la key ya que tanto para la encriptacion como desencriptacion no necesitaba guardarse referencia.

* Vigenere

    Este tda necesitaba guardarse ademas de la key, una referencia a la posicion de la key. Esto fue porque como se encripta de a partes(64 bytes) dependiendo del largo del archivo, el mensaje puede o no entrar en los 64 bytes por lo que para poder desencriptar "todo de una vez" tuvimos que guardarnos la refencia a la posicion de la key.

* RC4

    Este tda se guardar la la key, el vector de key_stream en donde lo inicializa por unica vez en la funcion de inicializacion de este tda y se guarda las refencias de i y j que afectarian en el rc4 prga. Esto se hace por el mismo motivo que mencione antes con el tda de vigenere con respecto a la desencriptacion.


# Deciciones de implementacion

Para la parte de encriptacion del lado del cliente, se decido que una vez leeido el mensaje de la entrada estandar se encripte y se envie el mensaje y como leemos de a 64 bytes eso lo hacemos dentro de la iteracion de lectora. Es por eso que la funcion de lector_iteral recibe dos punteros a funciones o como se puso en el tp dos callbacks donde uno es para el encriptar mensaje y recibe encapsulado al enciptador y el otro es para el mandar mensaje donde se recibe el socket. Esto se deicico asi para locarg mayor encapsulamiento y que si el dia de manana tenemos que cambiar ese callback por otro solo tendriamos que cambiar la firma de la funcion.

Para la parte del recibir en el tda socket tambien se recibe un puntero a funcion. En este caso se recibe la funcion de desencriptar mensaje y recibe al encriptador. Esto se hizo asi ya que como no sabemos el tamanio del mensaje que es recibido, la unica forma de imprimir todo el mensaje completo es o declaranado un buffer muy grande o pidiendo memoria. Es por eso que se decidio ir decodiifcando e imprimiento dentro de la funcion recibir asi evitamos pedir memoria.

En los dos programas se tiene implemnetado una funcion de verificacion de funcion, en la cual se verifica que tipo de cifrado se quiere utilizar para luego crear al encriptador generico con su cifrado correspondiente. Esto se hizo asi para luego poder delegar a al tipo de encritador.
A su vez se hace otra verificacion de lo mismo cuando se invoca a encriptador encriptar o encriptador desencriptar para poder saber de que cifrado se trata e invocar al correcto con su correspiende formato.

# Digramas

![digrama encriptador_t con sus tipos de encriptadores](https://github.com/agustinaa235/Tp1/blob/main/encriptadores.png)

![digrama con callbacks](https://github.com/agustinaa235/Tp1/blob/main/callbacks.png)
