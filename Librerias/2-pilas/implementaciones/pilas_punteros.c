#include "../p-firmas/pilas.h"
#include <stdio.h>
#include <stdlib.h>

// IMPLEMENTACION DE PILAS PARA ENTORNOS DONDE SE REALIZAN MUCHAS OPERACIONES DE APILADO O DESAPILADO
// PILAS CON TAMAÑO GRANDE O VARIABLE
// GESTION DINAMICA DE LA MEMORIA

static const int TAMANO_MAXIMO = 10;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/

struct Nodo{
    TipoElemento datos;
    struct Nodo* siguiente;
};

struct PilaRep{
    struct Nodo* tope;
};

/*===========================================================================================================*/
/*---FUNCIONES DE PILAS---*/

Pila p_crear(){
    Pila pila = (Pila)(malloc(sizeof(struct PilaRep)));
    pila->tope = NULL;
    return pila;
}
//
//
bool p_esta_vacia(Pila pila){
    return pila->tope == NULL;
}
//
//
int p_longitud(Pila pila){ //runtina interna, no forma parte del TAD
    int i = 0;
    struct Nodo* actual = pila->tope;
    while(actual != NULL){
        i++;
        actual = actual->siguiente;
    }
    return i;
}

bool p_esta_llena(Pila pila){
    return p_longitud(pila) == TAMANO_MAXIMO;
}
//
//
bool p_apilar(Pila pila, TipoElemento te){
    if(p_esta_llena(pila)){
        return false;
    }
    struct Nodo* apilado = malloc(sizeof(struct Nodo));
    apilado->datos = te;
    apilado->siguiente = pila->tope;
    pila->tope = apilado;
    return true;
}
//
//
TipoElemento p_desapilar(Pila pila){
    if(p_esta_vacia(pila)){
        return NULL;
    }
    struct Nodo* top = pila->tope;
    TipoElemento desapilado = top->datos;
    pila->tope = top->siguiente;
    free(top);
    return desapilado;
}
//
//
TipoElemento p_tope(Pila pila){
    if(p_esta_vacia(pila)){
        return NULL;
    }
    struct Nodo* top = pila->tope;
    return top->datos;
}
//
//
void p_mostrar(Pila pila){
    if(p_esta_vacia(pila)){
        printf("La pila esta vacia...\n");
        return;
    }
    struct Nodo* actual = pila->tope;
    printf("Tope -> ");
    while(actual != NULL){
        printf("[%i] ",actual->datos->clave);
        actual = actual->siguiente;
    }
}
/*===========================================================================================================*/