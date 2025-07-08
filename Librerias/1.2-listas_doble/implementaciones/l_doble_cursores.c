#include "../ld-firmas/listas-doble.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANO_MAXIMO = 100;
static const int NULO = -1; //simulacion de NULL

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct Nodo{
    TipoElemento datos;
    int siguiente; //indice del siguiente elemento
    int anterior;
};
//
struct ListaDobleRep{
    struct Nodo* cursor;
    int longitud;
    int inicio;
    int libre;
};
//
struct IteradorRep{
    ListaDoble lista;
    int pos_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS CON DOBLE ENLACE---*/
/*===========================================================================================================*/
//
ListaDoble ld_crear(){
    ListaDoble lista = (ListaDoble)(malloc(sizeof(struct ListaDobleRep)));
    lista->cursor = calloc(TAMANO_MAXIMO,sizeof(struct Nodo));
    lista->longitud = 0;

    for(int i=0; i < TAMANO_MAXIMO-2; i++){
        lista->cursor[i].siguiente = i+1; //enlazo el siguiente
        lista->cursor[i+1].anterior = i; //y el anterior
    }
    lista->cursor[TAMANO_MAXIMO-1].siguiente = NULO; //el ultimo no tiene siguiente
    lista->libre = 0;
    lista->inicio = NULO;
    return lista;
}
//
//
bool ld_esta_vacia(ListaDoble lista){
    return lista->inicio == NULO;
}
//
//
bool ld_esta_llena(ListaDoble lista){
    return lista->longitud == TAMANO_MAXIMO;
}
//
//
int ld_longitud(ListaDoble lista){
    return lista->longitud;
}
//
//
bool ld_agregar(ListaDoble lista, TipoElemento te){
    if(ld_esta_llena(lista)){
        return false;
    }

    int nuevo = lista->libre; //
    lista->libre = lista->cursor[nuevo].siguiente;

    lista->cursor[nuevo].siguiente = NULO;
    lista->cursor[nuevo].datos = te;

    if(ld_esta_vacia(lista)){
        lista->inicio = nuevo;
        lista->cursor[nuevo].anterior = NULO;
    }
    else{
        int q;
        q = lista->inicio;
        while(lista->cursor[q].siguiente != NULO){
            q = lista->cursor[q].siguiente;
        }
        lista->cursor[q].siguiente = nuevo;
        lista->cursor[nuevo].anterior = q;
    }
    lista->longitud++;
    return true;
}
//
//
bool ld_borrar(ListaDoble lista, int clave){
    if(ld_esta_vacia(lista)){
        return false;
    }

    bool borre = false;
    int ante, post; //nodos anterior y posterior al que se elimara
    int x = lista->inicio;

    //borrar apariciones sucesivas al inicio
    while((x != NULO) && (lista->cursor[x].datos->clave == clave)){
        //corro el inicio
        lista->inicio = lista->cursor[x].siguiente;
        if(lista->inicio != NULO){ //por si el nodo que borre es el ultimo que habia en la lista
            lista->cursor[lista->inicio].anterior = NULO;
        }
        //encadeno el nodo a eliminar con el arreglo de nodos libres
        lista->cursor[x].siguiente = lista->libre;
        lista->libre = x;
        //resto
        lista->longitud--;
        x = lista->inicio;
        borre = true;
    }

    //a este punto, "x" no tiene la clave a eliminar porque se eliminaron todas las apariciones al inicio
    //por lo que se ejecutara el else y se asignara valor a "ante" antes de usarse

    //borrar apariciones en el resto de la lista
    while((x != NULO)){
        if(lista->cursor[x].datos->clave == clave){
            post = lista->cursor[x].siguiente; //siguiente del nodo a eliminar
            //salteo el nodo a eliminar
            lista->cursor[ante].siguiente = post;
            if(post != NULO){
                lista->cursor[post].anterior = ante;
            }
            //encadeno el nodo a eliminar con el arreglo de nodos libres
            lista->cursor[x].siguiente = lista->libre;
            lista->libre = x;
            //resto
            lista->longitud--;
            borre = true;
        }
        else{
            ante = x;
            x = lista->cursor[x].siguiente;
        }
    }
}
//
//
TipoElemento ld_buscar(ListaDoble lista, int clave){
    int x = lista->inicio;
    while(x != NULO){
        if(lista->cursor[x].datos->clave == clave){
            return lista->cursor[x].datos;
        }
        x = lista->cursor[x].siguiente;
    }
    return NULL;
}
//
//
bool ld_insertar_pos(ListaDoble lista, TipoElemento te, int pos){
    if(ld_esta_llena(lista) || (pos < 1 || pos > ld_longitud(lista) + 1)){
        return false;
    }
    //si la posicion es al final, solo llamo a ld_agregar
    if(pos == ld_longitud(lista) + 1){
        return ld_agregar(lista,te);
    }
    //creo el nuevo nodo tomando una posicion de libres
    int nuevo = lista->libre;
    lista->libre = lista->cursor[nuevo].siguiente;
    lista->cursor[nuevo].datos = te;
    lista->cursor[nuevo].siguiente = NULO;
    lista->cursor[nuevo].anterior = NULO;

    if(pos == 1){ //agregar al inicio
        lista->cursor[nuevo].siguiente = lista->inicio;
        if(lista->inicio != NULO){
            lista->cursor[lista->inicio].anterior = nuevo;
        }
        lista->inicio = nuevo;
    }
    else{ //agregar en medio
        int ante = lista->inicio;
        for(int i=1; i < pos-1; i++){
            ante = lista->cursor[ante].siguiente;
        }
        int post = lista->cursor[ante].siguiente;

        lista->cursor[ante].siguiente = nuevo;
        lista->cursor[nuevo].anterior = ante;
        lista->cursor[nuevo].siguiente = post;
        if(post != NULO){
            lista->cursor[post].anterior = nuevo;
        }
    }
    lista->longitud++;
    return true;
}
//
//
bool ld_eliminar_pos(ListaDoble lista, int pos){
    if(ld_esta_vacia(lista) || (pos < 1 || pos > ld_longitud(lista))){
        return false;
    }
    
    int x = lista->inicio;
    if(pos == 1){
        lista->inicio = lista->cursor[x].siguiente;
        if(lista->inicio != NULO){
            lista->cursor[lista->inicio].anterior = NULO;
        }
        lista->cursor[x].siguiente = lista->libre;
        lista->libre = x;
    }
    else{
        //me paro en el nodo a eliminar
        for(int i=0; i < pos-1; i++){
            x = lista->cursor[x].siguiente;
        }
        int ante = lista->cursor[x].anterior;
        int post = lista->cursor[x].siguiente;
        //salteo el nodo
        lista->cursor[ante].siguiente = post;
        if(post != NULO){
            lista->cursor[post].anterior = ante;
        }
        //agrego el nodo eliminado a la lista de libres
        lista->cursor[x].siguiente = lista->libre;
        lista->libre = x;
    }
    lista->longitud--;
    return true;
}
//
//
TipoElemento ld_recuperar_pos(ListaDoble lista, int pos){
    if(ld_esta_vacia(lista) || (pos < 1 || pos > ld_longitud(lista))){
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
void ld_mostrar(ListaDoble lista){
    if(ld_esta_vacia(lista)){
        printf("\nLa lista esta vacia...");
    }
    else{
        int x = lista->inicio;
        printf("\nInicio -> ");
        while(x != NULO){
            printf("[%i] ", lista->cursor[x].datos->clave);
            x = lista->cursor[x].siguiente;
        }
    }
    printf("\n");
}
//
/*===========================================================================================================*/
/*---FUNCIONES DEL ITERADOR*/
/*===========================================================================================================*/
//
Iterador iterador(ListaDoble lista){
    Iterador iter = (Iterador)(malloc(sizeof(struct IteradorRep)));
    iter->lista = lista;
    iter->pos_actual = lista->inicio;
    return iter;
}
//
//
bool hay_siguiente(Iterador iter){
    return iter->pos_actual != NULO;
}
//
//
bool hay_anterior(Iterador iter){
    return(iter->pos_actual != NULO) && (iter->lista->cursor[iter->pos_actual].anterior != NULO);
}
//
//
TipoElemento siguiente(Iterador iter){
    TipoElemento te = NULL;
    if(iter->pos_actual != NULO){
        //devuelve primero, avanza despues
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
        //retrocede primero, devuelve despues
        iter->pos_actual = iter->lista->cursor[iter->pos_actual].anterior;
        te = iter->lista->cursor[iter->pos_actual].datos;
    }
    return te;
}
/*===========================================================================================================*/