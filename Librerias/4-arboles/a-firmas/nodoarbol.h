#ifndef NODOARBOL_H
#define NODOARBOL_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct NodoArbolRep{
    TipoElemento datos;
    struct NodoArbolRep* hi;
    struct NodoArbolRep* hd;
    int FE; //factor de equilibrio
};
typedef struct NodoArbolRep* NodoArbol;


/*-----FUNCIONES DE NODOARBOL-----*/
NodoArbol n_crear(TipoElemento te);
//
NodoArbol n_hijoizquierdo(NodoArbol padre);
//
NodoArbol n_hijoderecho(NodoArbol padre);
//
TipoElemento n_recuperar(NodoArbol nodo);

#endif //NODOARBOL_H