#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include "nodoarbol.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct ArbolBinarioRep;
typedef struct ArbolBinarioRep* ArbolBinario;

/*-----FUNCIONES DE ARBOL BINARIO-----*/
ArbolBinario a_crear();
//
bool a_esta_vacio(ArbolBinario A);
//
bool a_esta_lleno(ArbolBinario A);
//
int a_cantidad_elementos(ArbolBinario A);
//
bool a_rama_nula(NodoArbol nodo);
//
NodoArbol a_raiz(ArbolBinario A);
//
bool a_colocar_raiz(ArbolBinario A, NodoArbol nueva_raiz);
//
bool a_conectar_hi(ArbolBinario A, NodoArbol padre, TipoElemento te);
//
bool a_conectar_hd(ArbolBinario A, NodoArbol padre, TipoElemento te);

#endif //ARBOL_BINARIO_H