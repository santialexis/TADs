#ifndef PILAS_H
#define PILAS_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct PilaRep;
typedef struct PilaRep *Pila;

/*-----FUNCIONES DE PILAS-----*/
Pila p_crear();
//
bool p_esta_vacia(Pila pila);
//
bool p_esta_llena(Pila pila);
//
bool p_apilar(Pila pila, TipoElemento te);
//
TipoElemento p_desapilar(Pila pila);
//
TipoElemento p_tope(Pila pila);
//
void p_mostrar(Pila pila);

#endif //PILAS_H