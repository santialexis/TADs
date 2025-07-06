#ifndef COLAS_H
#define COLAS_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct ColaRep;
typedef struct ColaRep* Cola;

/*-----FUNCIONES DE COLAS-----*/
Cola c_crear();
//
bool c_esta_vacia(Cola cola);
//
bool c_esta_llena(Cola cola);
//
bool c_encolar(Cola cola, TipoElemento te);
//
TipoElemento c_desencolar(Cola cola);
//
TipoElemento c_frente(Cola cola);
//
void c_mostrar(Cola cola);

#endif //COLAS_H