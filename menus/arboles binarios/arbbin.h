#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "../../Librerias/TipoElemento/te-firmas/tipo_elemento.h"
#include "../../Librerias/1-listas/l-firmas/listas.h"
#include "../../Librerias/2-pilas/p-firmas/pilas.h"
#include "../../Librerias/3-colas/c-firmas/colas.h"
#include "../../Librerias/4-arboles/a-firmas/arbol_binario.h"

#ifndef ARBBIN_H
#define ARBBIN_H

void imprimir_nodos_nivel(NodoArbol nodo, int nivel_nodo, int nivel); //imprime los nodos de un nivel dado

#endif //