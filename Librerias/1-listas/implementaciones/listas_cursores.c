#include "../l-firmas/listas.h"
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
};
//
struct ListaRep{
    struct Nodo* cursor; //arreglo de nodos vacios
    int inicio;
    int libre; //indice del primer nodo libre
    int cantidad_elementos;
};
//
struct IteradorRep{
    Lista lista;
    int posicion;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS---*/
/*===========================================================================================================*/
//
Lista l_crear(){
    Lista lista = (Lista)(malloc(sizeof(struct ListaRep)));
    lista->cursor = calloc(TAMANO_MAXIMO,sizeof(struct Nodo));
    lista->cantidad_elementos = 0;

    //encadenar todos los nodos libres
    for(int i=0; i<=TAMANO_MAXIMO-2; i++){
        lista->cursor[i].siguiente = i+1; //el indice del siguiente sera el indice del actual +1, hasta TAMANO_MAXIMO-2 (98)
    }
    lista->cursor[TAMANO_MAXIMO-1].siguiente = NULO; //el siguiente del ultimo es NULL
    lista->libre = 0; //el primer nodo libre esta en la posicion 0
    lista->inicio = NULO; //el inicio de la lista vacia en NULL
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
        return false;
    }
    int p, q, qant;

    p = lista->libre; //guardo la primera posicion libre
    lista->libre = lista->cursor[p].siguiente; //el segundo nodo libre sera ahora el primero

    lista->cursor[p].datos = te;
    lista->cursor[p].siguiente = NULO;

    if(l_esta_vacia(lista)){
        lista->inicio = p;
    }
    else{
        q = lista->inicio;
        while(q != NULO){
            qant = q;
            q = lista->cursor[q].siguiente;
        }
        lista->cursor[qant].siguiente = q;
    }
    lista->cantidad_elementos++;
    return true;
}
//
//
bool l_borrar(Lista lista, int clave){
    if(l_esta_vacia(lista)){
        return false;
    }

    bool borre = false;
    int ante;
    int x = lista->inicio;

    //borrar apariciones al inicio
    while(x != NULO && lista->cursor[x].datos->clave == clave){
        lista->inicio = lista->cursor[x].siguiente; //muevo el inicio
        //encadeno el nodo x a la lista de libres
        lista->cursor[x].siguiente = lista->libre;
        lista->libre = x;
        lista->cantidad_elementos--;
        x = lista->inicio;
        borre = true;
    }

    while(x != NULO){
        if(lista->cursor[x].datos->clave == clave){
            //salteo el nodo con la clave a borrar
            lista->cursor[ante].siguiente = lista->cursor[x].siguiente;
            //encadeno x en la lista de libres
            lista->cursor[x].siguiente = lista->libre;
            lista->libre = x;
            //avanzo
            lista->cantidad_elementos--;
            x = lista->cursor[x].siguiente;
            borre = true;
        }
        else{
            ante = x;
            x = lista->cursor[x].siguiente;
        }
    }
    return borre;
}
//
//
TipoElemento l_buscar(Lista lista, int clave){
    if(l_esta_vacia(lista)){
        return NULL;
    }

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
bool l_insertar_pos(Lista lista, TipoElemento te, int pos){
    if(l_esta_llena(lista) || (pos < 1 || pos > l_longitud(lista) + 1)){
        return false;
    }
    
    if(pos == l_longitud(lista) + 1){ //insertar al final
        l_agregar(lista,te);
        return true;
    }

    //tomo un nodo libre para x
    int x = lista->libre;
    lista->libre = lista->cursor[x].siguiente;
    lista->cursor[x].datos = te;
    lista->cursor[x].siguiente = NULO;

    if(pos == 1){ //insertar al inicio
        lista->cursor[x].siguiente = lista->inicio;
        lista->inicio = x;
    }
    else{ //insertar dentro
        int aux = lista->inicio;
        for(int i=0; i<pos-2; i++){
            aux = lista->cursor[aux].siguiente;
        }
        lista->cursor[x].siguiente = lista->cursor[aux].siguiente;
        lista->cursor[aux].siguiente = x;
    }
    lista->cantidad_elementos++;
    return true;
}
//
//
bool l_eliminar_pos(Lista lista, int pos){
    if(l_esta_vacia(lista) || (pos < 1 || pos > l_longitud(lista))){
        return false;
    }

    int x = lista->inicio;
    if(pos == 1){
        lista->inicio = lista->cursor[x].siguiente;
        lista->cursor[x].siguiente = lista->libre;
        lista->libre = x;
    }
    else{
        int xsig;
        for(int i=0; i<pos-2; i++){ //me paro en el anterior del nodo a eliminar
            x = lista->cursor[x].siguiente;
        }
        xsig = lista->cursor[x].siguiente; //xsig = nodo a eliminar
        lista->cursor[x].siguiente = lista->cursor[xsig].siguiente; //salteo xsig
        //añado xsig al arreglo de libres
        lista->cursor[xsig].siguiente = lista->libre;
        lista->libre = xsig;
    }
    lista->cantidad_elementos--;
    return true;
}
//
//
TipoElemento l_recuperar_pos(Lista lista, int pos){
    if(l_esta_vacia(lista) || pos < 1 || pos > lista->cantidad_elementos){
        return NULL;
    }

    int x = lista->inicio;
    for(int i=0; i < pos-1; i++){
        x = lista->cursor[x].siguiente;
    }
    return lista->cursor[x].datos;
}
//
//
void l_mostrar(Lista lista){
    if(l_esta_vacia(lista)){
        printf("\nLa lista esta vacia...\n");
        return;
    }
    int x = lista->inicio;
    printf("\nInicio -> ");
    while(x != NULO){
        printf("[%i] ",lista->cursor[x].datos->clave);
        x = lista->cursor[x].siguiente;
    }
    printf("\n");
}
//
/*===========================================================================================================*/
/*---FUNCIONES DEL ITERADOR---*/
/*===========================================================================================================*/
//
Iterador iterador(Lista lista){
    Iterador iter = (Iterador)(malloc(sizeof(struct IteradorRep)));
    iter->lista = lista;
    iter->posicion = lista->inicio;
    return iter;
}
//
//
bool hay_siguiente(Iterador iter){
    return iter->posicion != NULO;
}
//
//
TipoElemento siguiente(Iterador iter){
    if(iter->posicion != NULO){
        TipoElemento te = iter->lista->cursor[iter->posicion].datos;
        iter->posicion = iter->lista->cursor[iter->posicion].siguiente;
        return te;
    }
    else{
        return NULL;
    }
}
/*===========================================================================================================*/