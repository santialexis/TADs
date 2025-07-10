#include "../cto-firmas/conjuntos.h"
#include "../../1-listas/l-firmas/listas.h"
#include <stdio.h>
#include <stdlib.h>

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
//
struct ConjuntoRep{
    Lista lista;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE CONJUNTOS---*/
/*===========================================================================================================*/
//
Conjunto cto_crear(){
    Conjunto conjunto = (Conjunto)(malloc(sizeof(struct ConjuntoRep)));
    conjunto->lista = l_crear();
    return conjunto;
}
//
//
bool cto_esta_vacio(Conjunto conjunto){
    return l_esta_vacia(conjunto->lista);
}
//
//
bool cto_esta_lleno(Conjunto conjunto){
    return l_esta_llena(conjunto->lista);
}
//
//
int cto_cantidad_elementos(Conjunto conjunto){
    return l_longitud(conjunto->lista);
}
//
//
bool cto_agregar(Conjunto conjunto, TipoElemento te){
    if(l_buscar(conjunto->lista,te->clave) == NULL){
        return l_agregar(conjunto->lista,te);
    }
    return false;
}
//
//
bool cto_borrar(Conjunto conjunto, int clave){
    return l_borrar(conjunto->lista, clave);
}
//
//
bool cto_pertenece(Conjunto conjunto, int clave){
    return l_buscar(conjunto->lista,clave) != NULL;
}
//
//
