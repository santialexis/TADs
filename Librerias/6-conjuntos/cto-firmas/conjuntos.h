#ifndef CONJUNTOS_H
#define CONJUNTOS_H

#include "../../TipoElemento/te-firmas/tipo_elemento.h"
#include <stdbool.h>

/*---ESTRUCTURA/S---*/
struct ConjuntoRep;
typedef struct ConjuntoRep* Conjunto;

/*-----FUNCIONES DE CONJUNTOS-----*/
Conjunto cto_crear();
//
bool cto_esta_vacio(Conjunto conjunto);
//
bool cto_esta_lleno(Conjunto conjunto);
//
int cto_cantidad_elementos(Conjunto conjunto);
//
bool cto_agregar(Conjunto conjunto, TipoElemento te);
//
bool cto_borrar(Conjunto conjunto, int clave);
//
bool cto_pertenece(Conjunto conjunto, int clave);
//
Conjunto cto_union(Conjunto cto_a, Conjunto cto_b); //elementos conjunto A + elementos conjunto B
//
Conjunto cto_interseccion(Conjunto cto_a, Conjunto cto_b); //elementos que estan tanto en el conjunto A como en el B
//
Conjunto cto_diferencia(Conjunto cto_a, Conjunto cto_b); //elementos del conjunto A que no estan en el B
//                                                       + elementos del conjunto B que no estan en el A
Conjunto cto_recuperar_pos(Conjunto conjunto, int pos);
//
void cto_mostrar(Conjunto conjunto);

#endif //CONJUNTOS_H