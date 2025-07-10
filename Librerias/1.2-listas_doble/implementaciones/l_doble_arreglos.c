#include "../ld-firmas/listas-doble.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANO_MAXIMO = 100;

//ESTA IMPLEMENTACION NO ES POSIBLE, SE DEBE USAR AL MENOS UN CURSOR !!!!!!!!!!!!
//POR ESO NO ESTA TERMINADA, PORQUE NO HACE FALTA

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct ListaDobleRep{
    TipoElemento* valores;
    int longitud;
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
    lista->valores = calloc(TAMANO_MAXIMO, sizeof(struct TipoElementoRep));
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

    lista->valores[lista->longitud] = te;
    lista->longitud++;
    return true;
}
//
//
bool ld_borrar(ListaDoble lista, int clave){
    if(ld_esta_vacia(lista)){
        return false;
    }

    int pos = 0;
    while(pos < lista->longitud){
        if(lista->valores[pos]->clave == clave){
            for(int i=0; i < ld_longitud-1; i++){
                lista->valores[i] = lista->valores[i+1];
            }
            lista->longitud--;
        }
        else{
            pos++;
        }
    }
    return true;
}
//
//
TipoElemento ld_buscar(ListaDoble lista, int clave){
    if(ld_esta_vacia(lista)){
        return false;
    }

    int pos = 0;
    while(pos < ld_longitud(lista)){
        if(lista->valores[pos]->clave == clave){
            return lista->valores[pos];
        }
    }
}