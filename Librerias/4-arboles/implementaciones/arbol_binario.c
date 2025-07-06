#include "../a-firmas/arbol_binario.h"
#include "../a-firmas/nodoarbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int TAMANO_MAXIMO = 100;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/

struct ArbolBinarioRep{
    NodoArbol raiz;
    int cantidad_elementos;
};

/*===========================================================================================================*/
/*---FUNCIONES DE ARBOLES BINARIOS---*/

ArbolBinario a_crear(){
    ArbolBinario A = (ArbolBinario)(malloc(sizeof(struct ArbolBinarioRep)));
    A->raiz = NULL;
    A->cantidad_elementos = 0;
    return A;
}
//
//
bool a_esta_vacio(ArbolBinario A){
    return A->cantidad_elementos == 0;
}
//
//
bool a_esta_lleno(ArbolBinario A){
    return A->cantidad_elementos == TAMANO_MAXIMO;
}
//
//
int a_cantidad_elementos(ArbolBinario A){
    return A->cantidad_elementos;
}
//
//
bool a_rama_nula(NodoArbol nodo){
    return nodo == NULL;
}
//
//
NodoArbol a_raiz(ArbolBinario A){
    return A->raiz;
}
//
//
bool a_colocar_raiz(ArbolBinario A, NodoArbol nueva_raiz){
    if(A->raiz != NULL){
        return false;
    }
    else{
        A->raiz = nueva_raiz;
        A->cantidad_elementos++;
        return true;
    }
}
//
//
bool a_conectar_hi(ArbolBinario A, NodoArbol padre, TipoElemento te){
    if(padre == NULL){
        return false;
    }
    if(padre->hi != NULL){
        return false;
    }
    NodoArbol hijoiz = n_crear(te);
    padre->hi = hijoiz;
    A->cantidad_elementos++;
    return true;
}
//
//
bool a_conectar_hd(ArbolBinario A, NodoArbol padre, TipoElemento te){
    if(padre == NULL){
        return false;
    }
    if(padre->hd != NULL){
        return false;
    }
    NodoArbol hijoder = n_crear(te);
    padre->hd = hijoder;
    A->cantidad_elementos++;
    return true;
}