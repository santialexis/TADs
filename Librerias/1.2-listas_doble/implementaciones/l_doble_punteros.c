#include "../ld-firmas/listas-doble.h"
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
struct ListaDobleRep{
    struct Nodo* inicio;
    int longitud;
};
//
struct IteradorRep{
    struct Nodo* pos_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS CON DOBLE ENLACE---*/
/*===========================================================================================================*/
//
ListaDoble ld_crear(){
    ListaDoble lista = (ListaDoble)(malloc(sizeof(struct ListaDobleRep)));
    lista->inicio = NULL;
    lista->longitud = 0;
    return lista;
}
//
//
bool ld_esta_vacia(ListaDoble lista){
    return lista->longitud == 0;
}
//
//
bool ld_esta_llena(ListaDoble lista){
    return lista->longitud == TAMANIO_MAXIMO;
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
    struct Nodo* nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = te;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = NULL;

    if(lista->inicio == NULL){
        lista->inicio = nuevo_nodo;
    }
    else{
        struct Nodo* aux = lista->inicio;
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = aux;
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
    struct Nodo* actual = lista->inicio;
    while((actual != NULL) && (actual->datos->clave == clave)){
        lista->inicio = actual->siguiente;
        free(actual);
        actual = lista->inicio;
        if(actual != NULL){
            actual->anterior = NULL;
        }
        lista->longitud--;
        borre = true;
    }

    while((actual != NULL) && (actual->siguiente != NULL)){
        if(actual->siguiente->datos->clave == clave){
            struct Nodo* proximo = actual->siguiente;
            actual->siguiente = proximo->siguiente;
            if(actual->siguiente != NULL){
                proximo->siguiente->anterior = actual;
            }
            free(proximo);
            lista->longitud--;
            borre = true;
        }
        else{
            actual = actual->siguiente;
        }
    }
    return borre;
}
//
//
TipoElemento ld_buscar(ListaDoble lista, int clave){
    struct Nodo* actual = lista->inicio;

    while(actual != NULL){
        if(actual->datos->clave == clave){
            return actual->datos;
        }
        else{
            actual = actual->siguiente;
        }
    }
    return NULL;
}
//
//
bool ld_insertar_pos(ListaDoble lista, TipoElemento te, int pos){
    if(ld_esta_llena(lista) || (pos < 1 || pos > ld_longitud(lista) + 1)){
        return false;
    }

    if(pos == ld_longitud(lista) + 1){
        return ld_agregar(lista,te);
    }

    struct Nodo* nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = te;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = NULL;

    if(pos == 1){
        nuevo_nodo->siguiente = lista->inicio;
        if(lista->inicio != NULL){
            lista->inicio->anterior = nuevo_nodo;
        }
        lista->inicio = nuevo_nodo;
    }
    else{
        struct Nodo* pos_ante = lista->inicio;
        for(int i=1; i<pos-1; i++){
            pos_ante = pos_ante->siguiente;
        }
        if(pos_ante->siguiente != NULL){
            pos_ante->siguiente->anterior = nuevo_nodo;
            nuevo_nodo->siguiente = pos_ante->siguiente;
        }
        pos_ante->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = pos_ante;
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

    struct Nodo* actual = lista->inicio;
    if(pos == 1){
        lista->inicio = actual->siguiente;
        if(lista->inicio != NULL){
            lista->inicio->anterior = NULL;
        }
        free(actual);
    }
    else{
        for(int i=1; i < pos-1; i++){
            actual = actual->siguiente;
        }

        struct Nodo* X = actual->siguiente;
        if(X->siguiente != NULL){
            X->siguiente->anterior = actual;
        }
        actual->siguiente = X->siguiente;
        free(X);
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
    
    struct Nodo* actual = lista->inicio;
    for(int i=0; i < pos-1; i++){
        actual = actual->siguiente;
    }
    return actual->datos;
}
//
//
void ld_mostrar(ListaDoble lista){
    if(ld_esta_vacia(lista)){
        printf("\nLa lista esta vacia...");
    }
    else{
        struct Nodo* actual = lista->inicio;
        printf("\nInicio -> ");
        while(actual != NULL){
            printf("[%i] ",actual->datos->clave);
            actual = actual->siguiente;
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
bool hay_anterior(Iterador iter){
    return (iter->pos_actual != NULL) && (iter->pos_actual->anterior != NULL);
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
        te = iter->pos_actual->datos;
        iter->pos_actual = iter->pos_actual->anterior;
    }
    return te;
}
/*===========================================================================================================*/