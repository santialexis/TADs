#include "../c-firmas/colas.h"
#include <stdio.h>
#include <stdlib.h>

// IMPLEMENTACION DE COLAS PARA ENTORNOS DONDE SE REALIZAN MUCHAS OPERACIONES DE ENCOLADO Y DESENCOLADO
// COLAS CON TAMAÑO GRANDE O VARIABLE
// GESTION DINAMICA DE LA MEMORIA

static const int TAMANO_MAXIMO = 10;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/

struct Nodo{
    TipoElemento datos;
    struct Nodo* siguiente;
};

struct ColaRep{
    struct Nodo* frente;
    struct Nodo* final;
};

/*===========================================================================================================*/
/*---FUNCIONES DE COLAS---*/

Cola c_crear(){
    Cola cola = (Cola)(malloc(sizeof(struct ColaRep)));
    cola->frente = NULL;
    cola->final = NULL;
    return cola;
}
//
//
bool c_esta_vacia(Cola cola){
    return cola->frente == NULL;
}
//
//
int c_longitud(Cola cola){ //runtina interna, no forma parte del TAD
    int i = 0;
    struct Nodo* actual = cola->frente;
    while(actual != NULL){
        i++;
        actual = actual->siguiente;
    }
    return i;
}

bool c_esta_llena(Cola cola){
    return c_longitud(cola) == TAMANO_MAXIMO;
}
//
//
bool c_encolar(Cola cola, TipoElemento te){
    if(c_esta_llena(cola)){
        return false;
    }
    struct Nodo* encolado;
    encolado->datos = te;
    encolado->siguiente = NULL;

    if(c_esta_vacia(cola)){
        cola->frente = encolado;
    }
    else {
        cola->final->siguiente = encolado;
    }
    cola->final = encolado;
    return true;
}
//
//
TipoElemento c_desencolar(Cola cola){
    if(c_esta_vacia(cola)){
        return NULL;
    }
    struct Nodo* front = cola->frente;
    TipoElemento desencolado = front->datos;
    cola->frente = front->siguiente;
    free(front);
    return desencolado;
}
//
//
TipoElemento c_frente(Cola cola){
    if(c_esta_vacia(cola)){
        return NULL;
    }
    return cola->frente->datos;
}
//
//
void c_mostrar(Cola cola){
    if(c_esta_vacia(cola)){
        printf("La cola esta vacia...\n");
        return;
    }
    struct Nodo* actual = cola->frente;
    printf("Frente -> ");
    while(actual != NULL){
        printf("[%i] ",actual->datos->clave);
        actual = actual->siguiente;
    }
}
/*===========================================================================================================*/