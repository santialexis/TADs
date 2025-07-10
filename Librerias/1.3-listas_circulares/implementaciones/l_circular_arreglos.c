#include "../lc-firmas/listas-circulares.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANIO_MAXIMO = 100;

//ESTA IMPLEMENTACION NO ES POSIBLE, SE DEBE USAR AL MENOS UN CURSOR !!!!!!!!!!!!
//POR ESO NO ESTA TERMINADA, PORQUE NO HACE FALTA

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct ListaCircRep{
    TipoElemento* valores;
    int inicio;
    int longitud;
};
//
struct IteradorRep{
    ListaCirc lista;
    int pos_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS CIRCULARES---*/
/*===========================================================================================================*/
//
ListaCirc lc_crear(){
    ListaCirc lista = (ListaCirc)(malloc(sizeof(struct ListaCircRep)));
    lista->valores = calloc(TAMANIO_MAXIMO, sizeof(struct TipoElementoRep));
    lista->inicio = 0;
    lista->longitud = 0;
    return lista;
}
//
//
TipoElemento lc_inicio(ListaCirc lista){
    if(lista->valores[lista->inicio] != NULL){
        return lista->valores[0];
    }
    return NULL;
}
//
//
TipoElemento lc_final(ListaCirc lista){
    int final = (lista->inicio + lista->longitud) % TAMANIO_MAXIMO;
    if(lista->valores[final] != NULL){
        return lista->valores[lista->longitud-1];
    }
    return NULL;
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
    int final = (lista->inicio + lista->longitud) % TAMANIO_MAXIMO;
    lista->valores[final] = te;
    lista->longitud++;
    return true;
}
//
//
bool lc_borrar(ListaCirc lista, int clave){
    if(lc_esta_vacia(lista)){
        return false;
    }

    bool borre = false;
    int nueva_long = 0; //longitud de la lista luego de borrar los elementos

    for(int i=0; i < lista->longitud; i++){ //recorro la lista entera
        int pos_real = (lista->inicio + i) % TAMANIO_MAXIMO; //posicion REAL del elemento actual

        if(lista->valores[pos_real]->clave != clave){ //si la clave NO DEBE ser borrada
            int pos = (lista->inicio + nueva_long) % TAMANIO_MAXIMO; //se calcula donde se posicionara en la lista
            lista->valores[pos] = lista->valores[pos_real]; //se coloca
            nueva_long++; //aumenta la longitud
        }
        else{ //si el elemento DEBE borrarse no lo agrego a la lista o "lo salteo"
            borre = true;
        }
    }
    lista->longitud = nueva_long; //actualizo la longitud
    return borre;
}
//
//
TipoElemento lc_buscar(ListaCirc lista, int clave){
    if(lc_esta_vacia(lista)){
        return NULL;
    }

    for(int i=0; i < lista->longitud; i++){
        int real = (lista->inicio + i) % TAMANIO_MAXIMO;
        if(lista->valores[real]->clave == clave){
            return lista->valores[real];
        }
    }
    return NULL;
}
//
//
bool lc_insertar_pos(ListaCirc lista, TipoElemento te, int pos){
    if(lc_esta_llena(lista) || (pos < 1 || pos > lc_longitud(lista) + 1)){
        return false;
    }

    if(pos == lc_longitud(lista) + 1){
        return lc_agregar(lista,te);
    }


}