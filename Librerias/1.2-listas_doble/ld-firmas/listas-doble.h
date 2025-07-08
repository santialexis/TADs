#include <stdbool.h>
#include "../../TipoElemento/te-firmas/tipo_elemento.h"

#ifndef LISTAS_DOBLE_H
#define LISTAS_DOBLE_H

/*---ESTRUCTURA/S---*/
struct ListaDobleRep;
typedef struct ListaDobleRep* ListaDoble;

struct IteradorRep;
typedef struct IteradorRep *Iterador;

/*-----FUNCIONES DE LISTAS DOBLES-----*/
ListaDoble ld_crear();
//
bool ld_esta_vacia(ListaDoble lista);
//
bool ld_esta_llena(ListaDoble lista);
//
int ld_longitud(ListaDoble lista);
//
bool ld_agregar(ListaDoble lista, TipoElemento te);
//
bool ld_borrar(ListaDoble lista, int clave);
//
TipoElemento ld_buscar(ListaDoble lista, int clave);
//
bool ld_insertar_pos(ListaDoble lista, TipoElemento te, int pos);
//
bool ld_eliminar_pos(ListaDoble lista, int pos);
//
TipoElemento ld_recuperar_pos(ListaDoble lista, int pos);
//
void ld_mostrar(ListaDoble lista);

/*-----FUNCIONES DE ITERADOR-----*/
Iterador iterador(ListaDoble lista);
//
bool hay_siguiente(Iterador iter);
//
bool hay_anterior(Iterador iter);
//
TipoElemento siguiente(Iterador iter);
//
TipoElemento anterior(Iterador iter);

#endif //LISTAS_DOBLE_H