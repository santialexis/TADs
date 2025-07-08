#include "../lc-firmas/listas-circulares.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANIO_MAXIMO = 100;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct Nodo{
    TipoElemento datos;
    struct Nodo* siguiente;
    struct Nodo* anterior;
};
//
struct ListaCircRep{
    struct Nodo* inicio;
    struct Nodo* final;
    int longitud;
};
//
struct IteradorRep{
    struct Nodo* pos_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS CIRCULARES---*/
/*===========================================================================================================*/
//
ListaCirc lc_crear(){
    ListaCirc lista = (ListaCirc)(malloc(sizeof(struct ListaCircRep)));
    lista->inicio = NULL;
    lista->final = NULL;
    lista->inicio->siguiente = lista->final;
    lista->final->anterior = lista->inicio;
    lista->longitud = 0;
    return lista;
}
//
//
TipoElemento lc_inicio(ListaCirc lista){
    if(lista->inicio == NULL){
        return NULL;
    }
    return lista->inicio->datos;
}
//
//
TipoElemento lc_final(ListaCirc lista){
    if(lista->final == NULL){
        return NULL;
    }
    return lista->final->datos;
}
//
//
bool lc_esta_vacia(ListaCirc lista){
    return lista->inicio == NULL;
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

    struct Nodo* nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = te;
    nuevo_nodo->siguiente = nuevo_nodo;
    nuevo_nodo->anterior = nuevo_nodo;

    if(lc_esta_vacia(lista)){
        lista->inicio = nuevo_nodo;
        lista->final = nuevo_nodo;
    }
    else{
        nuevo_nodo->siguiente = lista->inicio;
        nuevo_nodo->anterior = lista->final;

        lista->final->siguiente = nuevo_nodo;
        lista->inicio->anterior = nuevo_nodo;

        lista->final = nuevo_nodo;
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
    
    struct Nodo* actual = lista->inicio;
    int nodos = lc_longitud(lista); //contador para saber cuantos nodos debo recorrer (porque la lista es circular)
    bool borre = false;
    
    while(nodos > 0){ //mientras no haya recorrido todos los nodos
        if(actual->datos->clave == clave) //verifico la clave
        {
            if(lista->longitud == 1){ //si solo hay 1 nodo, "reinicio" la lista y termino aca
                free(actual);
                lista->inicio = NULL;
                lista->final = NULL;
                lista->longitud = 0;
                return true;
            }
            //si hay mas nodos, borro normalmente
            struct Nodo* ante = actual->anterior;
            struct Nodo* post = actual->siguiente;
            ante->siguiente = post;
            post->anterior = ante;

            if(actual == lista->inicio){ //si estoy eliminando el inicio
                lista->inicio = post; //lo actualizo
            }
            if(actual == lista->final){ //lo mismo con el final
                lista->final = ante;
            }

            free(actual); //libero
            actual = post; //avanzo
            lista->longitud--;
            borre = true;
        }
        else{
            actual = actual->siguiente;
        }
        nodos--; //un nodo menos que recorri
    }
    return borre;
}
//
//
TipoElemento lc_buscar(ListaCirc lista, int clave){
    struct Nodo* actual = lista->inicio;
    int nodos = lc_longitud(lista); //contador de longitud
    while(nodos > 0){
        if(actual->datos->clave == clave){
            return actual->datos;
        }
        actual = actual->siguiente;
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

    if(pos == lc_longitud(lista) + 1){ //si se pide insertar al final
        return lc_agregar(lista,te);
    }

    struct Nodo* nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = te;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = NULL;
    
    if(pos == 1){ //si se pide insertar al inicio
        nuevo_nodo->siguiente = lista->inicio;
        nuevo_nodo->anterior = lista->final;

        (lista->final)->siguiente = nuevo_nodo;
        (lista->inicio)->anterior = nuevo_nodo;

        lista->inicio = nuevo_nodo;
    }
    else{ //si se pide en medio
        struct Nodo* ante = lista->inicio; //el nodo anterior a donde ira el nuevo
        for(int i=1; i < pos-1; i++){
            ante = ante->siguiente;
        }
        struct Nodo* post = ante->siguiente; //el nodo posterior a donde ira el nuevo
        
        nuevo_nodo->siguiente = post;
        nuevo_nodo->anterior = ante;

        ante->siguiente = nuevo_nodo;
        post->anterior = nuevo_nodo;
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

    struct Nodo* x = lista->inicio;

    if(lc_longitud(lista) == 1){ //eliminar el unico elemento
        free(x);
        lista->inicio = NULL;
        lista->final = NULL;
        lista->longitud = 0;
        return true;
    }

    if(pos == 1){ //eliminar el inicio
        lista->inicio = x->siguiente;
        (lista->inicio)->anterior = lista->final;
        (lista->final)->siguiente = lista->inicio;
        free(x);
    }
    else if(pos == lc_longitud(lista)){ //eliminar el final
        x = lista->final;
        lista->final = x->anterior;
        (lista->inicio)->anterior = lista->final;
        (lista->final)->siguiente = lista->inicio;
        free(x);
    }
    else{ //eliminar el resto
        for(int i=1; i < pos; i++){ //me paro en el nodo a eliminar
            x = x->siguiente;
        }
        struct Nodo* ante = x->anterior;
        struct Nodo* post = x->siguiente;

        ante->siguiente = post;
        post->anterior = ante;
        free(x);
    }
    lista->longitud--;
    return true;
}
//
//
TipoElemento lc_recuperar_pos(ListaCirc lista, int pos){
    if(lc_esta_vacia(lista) || (pos < 1 || pos > lc_longitud(lista))){
        return NULL;
    }

    struct Nodo* x = lista->inicio;
    for(int i=1; i < pos; i++){
        x = x->siguiente;
    }
    return x->datos;
}
//
//
void lc_mostrar(ListaCirc lista){
    if(lc_esta_vacia(lista)){
        printf("\nLa lista esta vacia...");
    }
    else{
        struct Nodo* x = lista->inicio;
        printf("\nInicio -> ");
        for(int i=0; i < lista->longitud; i++){
            printf("[%i] ",x->datos->clave);
            x = x->siguiente;
        }
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
    iter->pos_actual = lista->inicio;
    return iter;
}
//
//
TipoElemento siguiente(Iterador iter){
    TipoElemento te = NULL;
    if(iter->pos_actual != NULL){
        te = iter->pos_actual->datos;
        iter->pos_actual = iter->pos_actual->siguiente;
    }
    return te;
}
//
//
TipoElemento anterior(Iterador iter){
    TipoElemento te = NULL;
    if(iter->pos_actual != NULL){
        iter->pos_actual = iter->pos_actual->anterior;
        te = iter->pos_actual->datos;
    }
    return te;
}
/*===========================================================================================================*/