#include "../a-firmas/binario_busqueda.h"
#include "../a-firmas/nodoarbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int TAMANO_MAXIMO = 100;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/

struct ArbolBinBusquedaRep{
    NodoArbol raiz;
    int cantidad_elementos;
};

/*===========================================================================================================*/
/*---FUNCIONES DE ARBOLES BINARIOS DE BUSQUEDA---*/

ArbolBinBusqueda abb_crear(){
    ArbolBinBusqueda ABB = (ArbolBinBusqueda)(malloc(sizeof(struct ArbolBinBusquedaRep)));
    ABB->raiz = NULL;
    ABB->cantidad_elementos = 0;
    return ABB;
}
//
//
bool abb_esta_vacio(ArbolBinBusqueda ABB){
    return ABB->cantidad_elementos == 0;
}
//
//
bool abb_esta_lleno(ArbolBinBusqueda ABB){
    return ABB->cantidad_elementos == TAMANO_MAXIMO;
}
//
//
int abb_cantidad_elementos(ArbolBinBusqueda ABB){
    return ABB->cantidad_elementos;
}
//
//
bool abb_rama_nula(NodoArbol nodo){
    return nodo == NULL;
}
//
//
NodoArbol abb_raiz(ArbolBinBusqueda ABB){
    return ABB->raiz;
}
//
//
bool abb_insertar(ArbolBinBusqueda ABB, TipoElemento te){
    if(abb_esta_lleno(ABB)){
        return false;
    }
    if(abb_esta_vacio(ABB)){
        ABB->raiz = n_crear(te);
        ABB->cantidad_elementos++;
        return true;
    }
    
    NodoArbol padre = NULL;
    NodoArbol aux = ABB->raiz;
    while(aux != NULL){
        padre = aux;
        if(te->clave < aux->datos->clave)
        {
            aux = aux->hi;
        }
        else if(te->clave > aux->datos->clave)
        {
            aux = aux->hd;
        }
        else{
            printf("Clave duplicada!: %i\n",te->clave);
            return false;
        }
    }

    if(te->clave < padre->datos->clave){
        padre->hi = n_crear(te);
    }
    else{
        padre->hd = n_crear(te);
    }
    ABB->cantidad_elementos++;
    return true;
}
//
//
/*eliminar_recursivo hacer*/

bool abb_eliminar(ArbolBinBusqueda ABB, int clave){
    if(abb_esta_vacio(ABB)){
        return false;
    }
    NodoArbol nodo;
    TipoElemento te_raiz = n_recuperar(ABB->raiz);

    //caso especifico: quiero borrar la raiz y esta solo tiene hijo izquierdo, el hi toma su lugar
    nodo = n_hijoderecho(ABB->raiz);
    if((nodo == NULL) && (te_raiz->clave == clave)){
        nodo = ABB->raiz;
        ABB->raiz = n_hijoizquierdo(ABB->raiz);
        free(nodo);
        return true;
    }

    //caso especifico: quiero borrar la raiz y esta solo tiene hijo derecho, el hd toma su lugar
    nodo = n_hijoizquierdo(ABB->raiz);
    if((nodo == NULL) && (te_raiz->clave == clave)){
        nodo = ABB->raiz;
        ABB->raiz = n_hijoderecho(ABB->raiz);
        free(nodo);
        return true;
    }
}
//
//
TipoElemento buscar_recursivo(NodoArbol actual, int clave){ /*rutina interna, no forma parte del TAD*/
    if(actual == NULL){
        return NULL;
    }
    else if(clave < actual->datos->clave){
        buscar_recursivo(actual->hi,clave);
    }
    else if(clave > actual->datos->clave){
        buscar_recursivo(actual->hd,clave);
    }
    else{
        return actual->datos;
    }
}

TipoElemento abb_buscar(ArbolBinBusqueda ABB, int clave){
    return buscar_recursivo(ABB->raiz,clave);
}