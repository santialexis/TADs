#include "../l-firmas/listas.h"
#include <stdio.h>
#include <stdlib.h>

static const int TAMANO_MAXIMO = 100;

/*===========================================================================================================*/
/*---ESTRUCTURAS---*/
/*===========================================================================================================*/
struct ListaRep{
    TipoElemento* valores;
    int cantidad;
};
//
struct IteradorRep{
    Lista lista;
    int posicion_actual;
};
//
/*===========================================================================================================*/
/*---FUNCIONES DE LISTAS---*/
/*===========================================================================================================*/
//
Lista l_crear(){
    Lista lista = (Lista)(malloc(sizeof(struct ListaRep)));
    lista->valores = calloc(TAMANO_MAXIMO,sizeof(struct TipoElementoRep));
    lista->cantidad = 0;
    return lista;
}
//
//
bool l_esta_vacia(Lista lista){
    return lista->cantidad == 0;
}
//
//
bool l_esta_llena(Lista lista){
    return lista->cantidad == TAMANO_MAXIMO;
}
//
//
int l_longitud(Lista lista){
    return lista->cantidad;
}
//
//
bool l_agregar(Lista lista, TipoElemento te){
    if(l_esta_llena(lista)){
        return false;
    }

    lista->valores[lista->cantidad] = te;
    lista->cantidad++;
    return true;
}
//
//
bool l_borrar(Lista lista, int clave){
    if(l_esta_vacia(lista)){
        return false;
    }

    int pos = 0;
    while(pos < lista->cantidad){
        if(lista->valores[pos]->clave == clave){
            for(int i=pos; i < lista->cantidad-1; i++){
                lista->valores[i] = lista->valores[i+1];
            }
            lista->cantidad--;
        }
        else{
            pos++;
        }
    }
    return true;
}
//
//
TipoElemento l_buscar(Lista lista, int clave){
    if(l_esta_vacia(lista)){
        return NULL;
    }

    int pos = 0;
    while(pos < lista->cantidad){
        if(lista->valores[pos]->clave == clave){
            return lista->valores[pos];
        }
        pos++;
    }
    return NULL;
}
//
//
bool l_insertar_pos(Lista lista, TipoElemento te, int pos){
    if(l_esta_llena(lista) || pos < 1 || pos > lista->cantidad + 1){
        return false;
    }

    //Ej: insertar un "3" en la posicion ordinal 3
    for(int i = lista->cantidad; i >= pos-1; i--){ //se corren todos los nodos 1 lugar a la derecha
        lista->valores[i] = lista->valores[i-1]; //[1,2,4,5,6,7,8] -> [1,2,2,4,5,6,7,8] se repite la pos anterior (2)
    }
    lista->valores[pos-1] = te; //[1,2,3,4,5,6,7,8] se pisa la pos ordinal 3 con el "3"
    lista->cantidad++;
    return true;
}
//
//
bool l_eliminar_pos(Lista lista, int pos){
    if(l_esta_vacia(lista) || pos < 1 || pos > lista->cantidad){
        return false;
    }

    //Ej: eliminar la pos ordinal 4 ("7")
    for(int i=pos-1; i < lista->cantidad-1; i++){ //[1,2,3,7,4,5] ->[1,2,3,4,5,5]
        lista->valores[i] = lista->valores[i+1];
    }
    lista->valores[lista->cantidad-1] = NULL;
    lista->cantidad--;
    return true;
}
//
//
TipoElemento l_recuperar_pos(Lista lista, int pos){
    if(l_esta_vacia(lista) || pos < 1 || pos > lista->cantidad){
        return NULL;
    }
    return lista->valores[pos-1];
}
//
//
void l_mostrar(Lista lista){
    if(l_esta_vacia(lista)){
        printf("\nLa lista esta vacia...\n");
    }
    else{
        printf("\nInicio -> ");
        for(int i=0; i < lista->cantidad; i++){
            printf("[%i] ",lista->valores[i]->clave);
        }
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
    iter->lista = lista;
    iter->posicion_actual = 0;
    return iter;
}
//
//
bool hay_siguiente(Iterador iter){
    return iter->posicion_actual < iter->lista->cantidad;
}
//
//
TipoElemento siguiente(Iterador iter){
    if(iter->posicion_actual < iter->lista->cantidad){
        return iter->lista->valores[iter->posicion_actual++]; //devuelve el te y avanza posicion
    }
    return NULL;
}
/*===========================================================================================================*/