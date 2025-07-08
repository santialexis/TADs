#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include <stdbool.h>

#ifndef LISTAS_CIRCULARES_H
#define LISTAS_CIRCULARES_H

/*---ESTRUCTURA/S---*/
struct ListaCircRep;
typedef struct ListaCircRep* ListaCirc;

struct IteradorRep;
typedef struct IteradorRep* Iterador;

/*---FUNCIONES DE LISTAS CIRCULARES---*/
ListaCirc lc_crear();
//
TipoElemento lc_inicio(ListaCirc lista);
//
TipoElemento lc_final(ListaCirc lista);
//
bool lc_esta_vacia(ListaCirc lista);
//
bool lc_esta_llena(ListaCirc lista);
//
int lc_longitud(ListaCirc lista);
//
bool lc_agregar(ListaCirc lista, TipoElemento te);
//
bool lc_borrar(ListaCirc lista, int clave);
//
TipoElemento lc_buscar(ListaCirc lista, int clave);
//
bool lc_insertar_pos(ListaCirc lista, TipoElemento te, int pos);
//
bool lc_eliminar_pos(ListaCirc lista, int pos);
//
TipoElemento lc_recuperar_pos(ListaCirc lista, int pos);
//
void lc_mostrar(ListaCirc lista);

/*---FUNCIONES DE ITERADOR---*/
Iterador iterador(ListaCirc lista);
//
TipoElemento siguiente(Iterador iter);
//
TipoElemento anterior(Iterador iter);

#endif //LISTAS_CIRCULARES_H