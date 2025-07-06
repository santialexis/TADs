#include "../l-firmas/listas.h"
#include <stdio.h>
#include <stdlib.h>

// IMPLEMENTACION DE LISTAS PARA ENTORNOS DONDE SE REALIZAN MUCHAS OPERACIONES DE INSERCION O ELIMINACION
// LISTA CON TAMAÑO GRANDE O VARIABLE
// GESTION DINAMICA DE LA MEMORIA

static const int TAMANO_MAXIMO = 100;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct Nodo{
    TipoElemento datos;
    struct Nodo* siguiente;
};
//
struct ListaRep{
    struct Nodo* inicio;
    int cantidad_elementos;
};
//
struct IteradorRep{
    struct Nodo* pos_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS---*/
/*===========================================================================================================*/
//
Lista l_crear(){
    Lista lista = (Lista)(malloc(sizeof(struct ListaRep))); //reservo memoria
    lista->inicio = NULL; //no hay elementos, inicio NULL
    lista->cantidad_elementos = 0; //no hay elementos
    return lista;
}
//
//
bool l_esta_vacia(Lista lista){
    return lista->cantidad_elementos == 0;
}
//
//
bool l_esta_llena(Lista lista){
    return lista->cantidad_elementos == TAMANO_MAXIMO;
}
//
//
int l_longitud(Lista lista){
    return lista->cantidad_elementos;
}
//
//
bool l_agregar(Lista lista, TipoElemento te){
    if(l_esta_llena(lista)){
        return false; //si esta llena, no se pudo agregar
    }

    struct Nodo* nodo_nuevo = malloc(sizeof(struct Nodo));
    nodo_nuevo->datos = te; //nodo que contendra al te
    nodo_nuevo->siguiente = NULL;

    if(lista->inicio == NULL){
        lista->inicio = nodo_nuevo; //si es el primer elemento, sera el inicio
    }
    else
    {
        struct Nodo* temp = lista->inicio; //nodo auxiliar para recorrer hasta encontrar el final
        while(temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        temp->siguiente = nodo_nuevo; //se agrega el nodo nuevo al final
    }

    lista->cantidad_elementos++; //1 elemento mas
    return true; //se pudo agregar el elemento
}
//
//
bool l_borrar(Lista lista, int clave){
    if(l_esta_vacia(lista)){
        return false; //si esta vacia, no se borro nada
    }

    bool borre = false;
    struct Nodo* actual = lista->inicio; //nodo para recorrer
    
    while((actual != NULL) && (actual->datos->clave == clave)) //borrar apariciones de la clave al inicio
    {
        lista->inicio = actual->siguiente; //nuevo inicio
        free(actual);
        lista->cantidad_elementos--;
        actual = lista->inicio; //reposiciono el nodo al nuevo inicio
        borre = true;
    }

    while((actual != NULL) && (actual->siguiente != NULL)) //borrar apariciones en el resto
    {
        if(actual->siguiente->datos->clave == clave) //si encontro clave:
        {
            struct Nodo* proximo = actual->siguiente;
            actual->siguiente = proximo->siguiente; //se saltea el nodo con la clave
            free(proximo);
            lista->cantidad_elementos--;
            borre = true;
        }
        else //si no encontro clave:
        {
            actual = actual->siguiente; //avanzo
        }
    }
    return borre;
}
//
//
TipoElemento l_buscar(Lista lista, int clave){
    struct Nodo* actual = lista->inicio;

    while(actual != NULL)
    {
        if(actual->datos->clave == clave){ //si encontre la clave:
            return actual->datos; //la retorno
        }
        else{
            actual = actual->siguiente; //sino: avanzo
        }
    }
    return NULL;
}
//
//
bool l_insertar_pos(Lista lista, TipoElemento te, int pos){
    if(l_esta_llena(lista) || ((pos < 1) || (pos > l_longitud(lista) + 1))){
        return false; //lista llena o pos invalida
    }

    if(pos == l_longitud(lista)+1){ //si pos es la posicion final:
        l_agregar(lista,te); //agrego al final
        return true;
    }

    struct Nodo* nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = te; //creo el nuevo nodo
    nuevo_nodo->siguiente = NULL;

    if(pos == 1){ //si pos es 1:
        nuevo_nodo->siguiente = lista->inicio; //nuevo_nodo sera el inicio
        lista->inicio = nuevo_nodo;
    }
    else //sino:
    {
        struct Nodo* anterior = lista->inicio; //nodo para recorrer
        
        for(int i=1; i<pos-1; i++){
            anterior = anterior->siguiente; //me paro en el nodo anterior a pos
        }
        nuevo_nodo->siguiente = anterior->siguiente;
        anterior->siguiente = nuevo_nodo;
    }
    lista->cantidad_elementos++;
    return true;
}
//
//
bool l_eliminar_pos(Lista lista, int pos){
    if(l_esta_vacia(lista)){
        return false; //lista vacia
    }

    if((pos < 1) || (pos > l_longitud(lista))){
        return false; //posicion invalida
    }

    bool borre = false;
    struct Nodo* actual = lista->inicio;

    if(pos == 1){ //si quiero eliminar el inicio:
        lista->inicio = actual->siguiente; //el inicio sera el siguiente
        free(actual);
    }
    else //sino:
    {
        for(int i=1; i<pos-1; i++){
            actual = actual->siguiente; //busco el nodo anterior al que quiero eliminar
        }
        struct Nodo* nodo_borrado = actual->siguiente;
        actual->siguiente = nodo_borrado->siguiente; //lo salteo
        free(nodo_borrado);
    }
    lista->cantidad_elementos--;
    return true;
}
//
//
TipoElemento l_recuperar_pos(Lista lista, int pos){
    if(l_esta_vacia(lista)){
        return NULL; //lista vacia
    }

    if((pos < 1) || (pos > l_longitud(lista))){
        return NULL; //posicion invalida
    }

    struct Nodo* actual = lista->inicio;
    for(int i=1; i<pos; i++){
        actual = actual->siguiente; //busco la posicion y la retorno
    }
    return actual->datos;
}
//
//
void l_mostrar(Lista lista){
    if(l_esta_vacia(lista)){
        printf("La lista esta vacia...\n");
        return;
    }

    struct Nodo* actual = lista->inicio;
    printf("Contenido de la lista: ");
    while(actual != NULL){
        printf("[%d] ",actual->datos->clave); //imprimo cada dato de la lista
        actual = actual->siguiente;
    }
    printf("\n");
}
//
/*===========================================================================================================*/
/*---FUNCIONES DEL ITERADOR*/
/*===========================================================================================================*/
//
Iterador iterador(Lista lista){
    Iterador iter = (Iterador)(malloc(sizeof(struct IteradorRep)));
    iter->pos_actual = lista->inicio;
    return iter;
}
//
//
bool hay_siguiente(Iterador iter){
    return iter->pos_actual != NULL;
}
//
//
TipoElemento siguiente(Iterador iter){
    if(hay_siguiente(iter)){
        TipoElemento dato = iter->pos_actual->datos;
        iter->pos_actual = iter->pos_actual->siguiente;
        return dato;
    }
    else
    {
        return NULL;
    }
}
/*===========================================================================================================*/