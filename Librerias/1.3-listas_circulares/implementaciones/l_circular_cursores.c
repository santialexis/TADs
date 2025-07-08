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
bool lc_borrar(ListaCirc lista, int clave){
    if(lc_esta_vacia(lista)){
        return false;
    }

    int actual = lista->inicio;
    int nodos = lc_longitud(lista);
    bool borre = false;

    while(nodos > 0){ //mientra haya nodos por recorrer (sin repetir)
        int sig = lista->cursor[actual].siguiente;

        if(lista->cursor[actual].datos->clave == clave){ //comparo las claves
            if(lista->longitud == 1){ //caso 1: lista con 1 solo elemento, "reinicio" la lista
                lista->inicio = NULO;
                lista->final = NULO;
                lista->libre = 0;
                lista->longitud = 0;
                return true;
            }
            int ante = lista->cursor[actual].anterior;
            int post = lista->cursor[actual].siguiente;

            lista->cursor[ante].siguiente = post;
            lista->cursor[post].anterior = ante;

            lista->cursor[actual].siguiente = lista->libre;
            lista->libre = actual;

            if(actual == lista->inicio){
                lista->inicio = post;
            }
            if(actual == lista->final){
                lista->final = ante;
            }

            lista->longitud--;
            borre = true;
        }
        actual = sig;
        nodos--;
    }
    return borre;
}
//
//
TipoElemento lc_buscar(ListaCirc lista, int clave){
    int nodos = lista->longitud;
    int x = lista->inicio;

    while(nodos > 0){
        if(lista->cursor[x].datos->clave == clave){
            return lista->cursor[x].datos;
        }
        x = lista->cursor[x].siguiente;
        nodos--;
    }
    return NULL;
}
//
//
bool lc_insertar_pos(ListaCirc lista, TipoElemento te, int pos){
    if(lc_esta_llena(lista) || (pos < 1 || pos > lc_longitud(lista) + 1)){
        return false;
    }

    if(pos == lc_longitud(lista) + 1){ //insertar al final
        return lc_agregar(lista,te);
    }

    int nuevo_nodo = lista->libre; //tomo un nodo del arreglo de libres
    lista->libre = lista->cursor[nuevo_nodo].siguiente;

    lista->cursor[nuevo_nodo].datos = te;

    if(pos == 1){ //insertar al inicio
        lista->cursor[nuevo_nodo].siguiente = lista->inicio;
        lista->cursor[nuevo_nodo].anterior = lista->final;

        lista->cursor[lista->final].siguiente = nuevo_nodo;
        lista->cursor[lista->inicio].anterior = nuevo_nodo;

        lista->inicio = nuevo_nodo;
    }
    else{ //insertar en medio
        int ante = lista->inicio;
        for(int i=1; i < pos-1; i++){
            ante = lista->cursor[ante].siguiente;
        }
        int post = lista->cursor[ante].siguiente;

        lista->cursor[nuevo_nodo].siguiente = post;
        lista->cursor[nuevo_nodo].anterior = ante;

        lista->cursor[ante].siguiente = nuevo_nodo;
        lista->cursor[post].anterior = nuevo_nodo;
    }
    lista->longitud++;
    return true;
}
//
//
bool lc_eliminar_pos(ListaCirc lista, int pos){
    if(lc_esta_vacia(lista) || (pos < 1 || pos > lc_longitud(lista))){
        return false;
    }

    int x = lista->inicio;

    if(lc_longitud(lista) == 1){ //si elimino el unico elemento de la lista, la "reinicio" y termino
        lista->cursor[x].siguiente = lista->libre;
        lista->libre = x;

        lista->inicio = NULO;
        lista->final = NULO;
        lista->longitud = 0;
        return true;
    }

    if(pos == 1){ //eliminar el inicio
        lista->inicio = lista->cursor[x].siguiente;

        lista->cursor[lista->final].siguiente = lista->inicio;
        lista->cursor[lista->inicio].anterior = lista->final;
    }
    else if(pos == lc_longitud(lista)){ //eliminar el final
        x = lista->final;
        lista->final = lista->cursor[x].anterior;

        lista->cursor[lista->final].siguiente = lista->inicio;
        lista->cursor[lista->inicio].anterior = lista->final;
    }
    else{ //eliminar en medio
        for(int i=1; i < pos; i++){
            x = lista->cursor[x].siguiente;
        }
        int ante = lista->cursor[x].anterior;
        int post = lista->cursor[x].siguiente;

        lista->cursor[ante].siguiente = post;
        lista->cursor[post].anterior = ante;
    }
    lista->cursor[x].siguiente = lista->libre;
    lista->libre = x;
    
    lista->longitud--;
    return true;
}
//
//
TipoElemento lc_recuperar_pos(ListaCirc lista, int pos){
    if(lc_esta_vacia(lista) || (pos < 1 || pos > lc_longitud(lista))){
        return NULL;
    }

    int x = lista->inicio;
    for(int i=1; i < pos; i++){
        x = lista->cursor[x].siguiente;
    }
    return lista->cursor[x].datos;
}
//
//
void lc_mostrar(ListaCirc lista){
    if(lc_esta_vacia(lista)){
        printf("\nLa lista esta vacia...");
    }
    else{
        int x = lista->inicio;
        printf("\nInicio -> ");
        for(int i=0; i < lista->longitud; i++){
            printf("[%i] ",lista->cursor[x].datos->clave);
            x = lista->cursor[x].siguiente;
        }
        printf(" -> Vuelta al inicio");
    }
    printf("\n");
}
//
/*===========================================================================================================*/
/*---FUNCIONES DEL ITERADOR---*/
/*===========================================================================================================*/
//
Iterador iterador(ListaCirc lista){
    Iterador iter = (Iterador)(malloc(sizeof(struct IteradorRep)));
    iter->lista = lista;
    iter->pos_actual = lista->inicio;
    return iter;
}
//
//
TipoElemento siguiente(Iterador iter){
    TipoElemento te = NULL;
    if(iter->pos_actual != NULO){
        te = iter->lista->cursor[iter->pos_actual].datos;
        iter->pos_actual = iter->lista->cursor[iter->pos_actual].siguiente;
    }
    return te;
}
//
//
TipoElemento anterior(Iterador iter){
    TipoElemento te = NULL;
    if(iter->pos_actual != NULO){
        iter->pos_actual = iter->lista->cursor[iter->pos_actual].anterior;
        te = iter->lista->cursor[iter->pos_actual].datos;
    }
    return te;
}
/*===========================================================================================================*/