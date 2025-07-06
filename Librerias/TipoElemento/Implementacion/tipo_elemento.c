#include "../te-firmas/tipo_elemento.h"
#include <stdlib.h>

//
TipoElemento te_crear(int clave){
    TipoElemento te = (TipoElemento)(malloc(sizeof(struct TipoElementoRep))); //reservo memoria
    te->clave = clave; //asigno clave
    te->valor = NULL; //asigno valor NULL
    return te;
}
//
TipoElemento te_crear_con_valor(int clave, void* valor){
    TipoElemento te = (TipoElemento)(malloc(sizeof(struct TipoElementoRep))); //asigno memoria
    te->clave = clave; //asigno clave
    te->valor = valor; //asigno valor
    return te;
}