#include "../a-firmas/nodoarbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodoArbol n_crear(TipoElemento te){
    NodoArbol nodo = (NodoArbol)(malloc(sizeof(struct NodoArbolRep)));
    nodo->datos = te;
    nodo->hi = NULL;
    nodo->hd = NULL;
    nodo->FE = 0;
    return nodo;
}
//
//
NodoArbol n_hijoizquierdo(NodoArbol padre){
    if(padre == NULL){
        return NULL;
    }
    else{
        return padre->hi;
    }
}
//
//
NodoArbol n_hijoderecho(NodoArbol padre){
    if(padre == NULL){
        return NULL;
    }
    else{
        return padre->hd;
    }
}
//
//
TipoElemento n_recuperar(NodoArbol nodo){
    if(nodo == NULL){
        return NULL;
    }
    else{
        return nodo->datos;
    }
}