#include "../lc-firmas/listas-circulares.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANIO_MAXIMO = 100;
static const int NULO = -1;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct Nodo{
    TipoElemento datos;
    int siguiente;
    int anterior;
};
//
struct ListaCircRep{
    struct Nodo* cursor;
    int inicio;
    int final;
    int libre;
    int longitud;
};
//
struct IteradorRep{
    ListaCirc lista;
    int pos_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS CON DOBLE ENLACE---*/
/*===========================================================================================================*/
//
ListaCirc lc_crear(){
    ListaCirc lista = (ListaCirc)(malloc(sizeof(struct ListaCircRep)));
    lista->cursor = calloc(TAMANIO_MAXIMO,sizeof(struct Nodo));

    for(int i=0; i < TAMANIO_MAXIMO-1; i++){
        lista->cursor[i].siguiente = i+1;
        lista->cursor[i+1].anterior = i;
    }
    lista->cursor[TAMANIO_MAXIMO-1].siguiente = NULO;

    lista->inicio = NULO;
    lista->final = NULO;
    lista->libre = 0;
    lista->longitud = 0;
    return lista;
}
//
//
TipoElemento lc_inicio(ListaCirc lista){
    if(lista->longitud == 0){
        return NULL;
    }
    return lista->cursor[lista->inicio].datos;
}
//
//
TipoElemento lc_final(ListaCirc lista){
    if(lista->longitud == 0){
        return NULL;
    }
    return lista->cursor[lista->final].datos;
}
//
//
bool lc_esta_vacia(ListaCirc lista){
    return lista->longitud == 0;
}
//
//
bool lc_esta_llena(ListaCirc lista){
    return lista->longitud == TAMANIO_MAXIMO;
}
//
//
int lc_longitud(ListaCirc lista){
    return lista->longitud;
}
//
//
bool lc_agregar(ListaCirc lista, TipoElemento te){
    if(lc_esta_llena(lista)){
        return false;
    }

    int nodo_nuevo = lista->libre;
    lista->libre = lista->cursor[nodo_nuevo].siguiente;

    lista->cursor[nodo_nuevo].datos = te;

    if(lc_esta_vacia(lista)){
        lista->inicio = nodo_nuevo;
        lista->final = nodo_nuevo;

        lista->cursor[nodo_nuevo].siguiente = nodo_nuevo;
        lista->cursor[nodo_nuevo].anterior = nodo_nuevo;
    }
    else{
        lista->cursor[nodo_nuevo].siguiente = lista->inicio;
        lista->cursor[nodo_nuevo].anterior = lista->final;

        lista->cursor[lista->final].siguiente = nodo_nuevo;
        lista->cursor[lista->inicio].anterior = nodo_nuevo;

        lista->final = nodo_nuevo;
    }
    lista->longitud++;
    return true;
}
//
//
