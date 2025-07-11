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
Conjunto cto_union(Conjunto cto_a, Conjunto cto_b){
    Conjunto res = cto_crear();
    Iterador iter = iterador(cto_a->lista);
    while(hay_siguiente(iter)){
        cto_agregar(res, siguiente(iter));
    }
    free(iter);

    iter = iterador(cto_b->lista);
    while(hay_siguiente(iter)){
        cto_agregar(res,siguiente(iter));
    }
    free(iter);
    return res;
}
//
//
Conjunto cto_interseccion(Conjunto cto_a, Conjunto cto_b){
    Conjunto res = cto_crear();
    Iterador iter = iterador(cto_a->lista);
    while(hay_siguiente(iter)){
        TipoElemento te = siguiente(iter);
        if(cto_pertenece(cto_b,te->clave)){
            cto_agregar(res,te);
        }
    }
    free(iter);
    return res;
}
//
//
Conjunto cto_diferencia(Conjunto cto_a, Conjunto cto_b){
    Conjunto res = cto_crear();
    Iterador iter = iterador(cto_a->lista);
    while(hay_siguiente(iter)){
        TipoElemento te = siguiente(iter);
        if(!cto_pertenece(cto_b,te->clave)){
            cto_agregar(res,te);
        }
    }
    free(iter);
    return res;
}
//
//
TipoElemento cto_recuperar_pos(Conjunto conjunto, int pos){
    return l_recuperar_pos(conjunto->lista,pos);
}
//
//
void cto_mostrar(Conjunto conjunto){
    if(cto_esta_vacio(conjunto)){
        printf("\nEl conjunto esta vacio...\n");
    }
    else{
        l_mostrar(conjunto->lista);
    }
}/*===========================================================================================================*/