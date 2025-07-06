#ifndef BINARIO_BUSQUEDA_H
#define BINARIO_BUSQUEDA_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include "nodoarbol.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct ArbolBinBusquedaRep;
typedef struct ArbolBinBusquedaRep* ArbolBinBusqueda;

/*-----FUNCIONES DE ARBOL BINARIO DE BUSQUEDA-----*/
ArbolBinBusqueda abb_crear();
//
bool abb_esta_vacio(ArbolBinBusqueda ABB);
//
bool abb_esta_lleno(ArbolBinBusqueda ABB);
//
int abb_cantidad_elementos(ArbolBinBusqueda ABB);
//
bool abb_rama_nula(NodoArbol nodo);
//
NodoArbol abb_raiz(ArbolBinBusqueda);
//
bool abb_insertar(ArbolBinBusqueda ABB, TipoElemento te);
//
bool abb_eliminar(ArbolBinBusqueda ABB, int clave);
//
TipoElemento abb_buscar(ArbolBinBusqueda ABB, int clave);

#endif //BINARIO_BUSQUEDA_H