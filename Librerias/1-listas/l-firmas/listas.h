#ifndef LISTAS_H
#define LISTAS_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct ListaRep;
typedef struct ListaRep *Lista;

struct IteradorRep;
typedef struct IteradorRep *Iterador;

/*-----FUNCIONES DE LISTAS-----*/
Lista l_crear();
//
bool l_esta_vacia(Lista lista);
//
bool l_esta_llena(Lista lista);
//
int l_longitud(Lista lista);
//
bool l_agregar(Lista lista, TipoElemento te);
//
bool l_borrar(Lista lista, int clave);
//
TipoElemento l_buscar(Lista lista, int clave);
//
bool l_insertar_pos(Lista lista, TipoElemento te, int pos);
//
bool l_eliminar_pos(Lista lista, int pos);
//
TipoElemento l_recuperar_pos(Lista lista, int pos);
//
void l_mostrar(Lista lista);

/*-----FUNCIONES DE ITERADOR-----*/
Iterador iterador(Lista lista);
//
bool hay_siguiente(Iterador iter);
//
TipoElemento siguiente(Iterador iter);

#endif //LISTAS_H