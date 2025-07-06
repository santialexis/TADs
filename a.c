#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "Librerias/TipoElemento/te-firmas/tipo_elemento.h"
#include "Librerias/1-listas/l-firmas/listas.h"
#include "Librerias/2-pilas/p-firmas/pilas.h"
#include "Librerias/3-colas/c-firmas/colas.h"
#include "Librerias/4-arboles/a-firmas/arbol_binario.h"

void nodos_nivel(NodoArbol actual, int nivel, int nivel_actual){
    if(ab_rama_nula(actual)){
        return;
    }

    TipoElemento te = n_recuperar(actual);
    if(nivel_actual == nivel){
        printf("[%i] ",te->clave);
        return;
    }

    NodoArbol hi = n_hijoizquierdo(actual);
    NodoArbol hd = n_hijoderecho(actual);

    nodos_nivel(hi,nivel,nivel_actual+1);
    nodos_nivel(hd,nivel,nivel_actual+1);
}

void principal1(ArbolBinario AB, int nivel){
    if(ab_esta_vacio(AB)){
        printf("Arbol vacio...\n");
    }
    else{
        nodos_nivel(ab_raiz(AB), nivel, 0);
    }
}

/*=================================================================================*/

bool es_abb(NodoArbol actual, int min, int max){
    if(ab_rama_nula(actual)){
        return true;
    }

    int clave_actual = n_recuperar(actual)->clave;
    
    if((clave_actual <= min) || (clave_actual >= max)){
        return false;
    }

    NodoArbol hi = n_hijoizquierdo(actual);
    NodoArbol hd = n_hijoderecho(actual);

    return es_abb(hi,min,clave_actual) && es_abb(hd,clave_actual,max);
}

bool principal2(ArbolBinario AB){
    if(ab_esta_vacio(AB)){
        printf("Arbol vacio...");
        return false;
    }
    return es_abb(ab_raiz(AB),-100000000,100000000);
}

//

void es_bin_bus(NodoArbol nodo, Lista lista){
    if(ab_rama_nula(nodo)){
        return;
    }
    es_bin_bus(n_hijoizquierdo(nodo),lista);
    l_agregar(lista,nodo);
    es_bin_bus(n_hijoderecho(nodo),lista);
}

bool sas(ArbolBinario AB){
    bool si_es_abb = true;
    if(ab_esta_vacio(AB)){
        si_es_abb = false;
    }
    else{
        Lista lista = l_crear();
        es_bin_bus(ab_raiz(AB),lista);

        Iterador iter = iterador(lista);
        TipoElemento te1 = siguiente(iter);

        while(hay_siguiente(iter)){
            TipoElemento te2 = siguiente(iter);
            if(te1->clave > te2->clave){
                si_es_abb = false;
            }
            te1 = te2;
        }
    }
    return si_es_abb;
}

/*=============================================================================*/

void preorden(NodoArbol actual){
    if(ab_rama_nula(actual)){
        return;
    }
    printf("[%i] ",n_recuperar(actual)->clave);
    preorden(n_hijoizquierdo(actual));
    preorden(n_hijoderecho(actual));
}

void inorden(NodoArbol actual){
    if(ab_rama_nula(actual)){
        return;
    }
    inorden(n_hijoizquierdo(actual));
    printf("[%i] ",n_recuperar(actual)->clave);
    inorden(n_hijoderecho(actual));
}

void postorden(NodoArbol actual){
    if(ab_rama_nula(actual)){
        return;
    }
    postorden(n_hijoizquierdo(actual));
    postorden(n_hijoderecho(actual));
    printf("[%i] ",n_recuperar(actual)->clave);
}

/*=============================================================================*/

void suma_hojas(NodoArbol nodo, int* suma){
    if(ab_rama_nula(nodo)){
        return;
    }

    NodoArbol hi = n_hijoizquierdo(nodo);
    NodoArbol hd = n_hijoderecho(nodo);

    if(ab_rama_nula(hi) && ab_rama_nula(hd)){
        *suma += n_recuperar(nodo)->clave;
    }

    suma_hojas(hi,suma);
    suma_hojas(hd,suma);
}

/*=============================================================================*/

void imprimir_ancestros(Pila pila){
    Pila aux = p_crear();
    TipoElemento te;

    while(!p_esta_vacia(pila)){
        te = p_desapilar(pila);
        p_apilar(aux,te);
    }

    printf("\nRaiz -> ");
    while(!p_esta_vacia(aux)){
        te = p_desapilar(aux);
        printf("[%i] ",te->clave);
        p_apilar(pila,te);
    }
}

void buscar_nodo(NodoArbol nodo, int clave, Pila pila){
    if(ab_rama_nula(nodo)){
        return;
    }

    if(n_recuperar(nodo)->clave == clave){
        imprimir_ancestros(pila);
        return;
    }

    p_apilar(pila,n_recuperar(nodo));

    NodoArbol hi = n_hijoizquierdo(nodo);
    NodoArbol hd = n_hijoderecho(nodo);

    buscar_nodo(hi,clave,pila);
    buscar_nodo(hd,clave,pila);
    p_desapilar(pila);
}

/*=========================================================================*/

void contar_nivel(NodoArbol nodo, int nivel, int nivel_actual, int* cantidad){
    if(ab_rama_nula(nodo)){
        return;
    }

    if(nivel_actual == nivel){
        (*cantidad)++;
    }

    contar_nivel(n_hijoizquierdo(nodo),nivel,nivel_actual+1,cantidad);
    contar_nivel(n_hijoderecho(nodo),nivel,nivel_actual+1,cantidad);
}

/*=============================================================================*/

void contar_hijos_nario(NodoArbol nodo, int clave, int* acc){
    if(ab_rama_nula(nodo)){
        return;
    }

    NodoArbol hijo = n_hijoizquierdo(nodo);

    if(n_recuperar(nodo)->clave == clave){
        while(!ab_rama_nula(hijo)){
            (*acc)++;
            hijo = n_hijoderecho(hijo);
        }
        return;
    }

    contar_hijos_nario(hijo,clave,acc);
    contar_hijos_nario(n_hijoderecho(nodo),clave,acc);
}

/*========================================================================*/

void altura_nario(NodoArbol nodo, int altura_actual, int* altura){
    if(ab_rama_nula(nodo)){
        return;
    }

    NodoArbol hi = n_hijoizquierdo(nodo);
    NodoArbol hd = n_hijoderecho(nodo);

    if(ab_rama_nula(hi) && altura_actual > *altura){
        *altura = altura_actual;
    }

    altura_nario(hi,altura_actual+1,altura);
    altura_nario(hd,altura_actual,altura);
}

void buscar_nodo_nario(NodoArbol nodo, int clave, int* altura){
    if(ab_rama_nula(nodo)){
        return;
    }

    if(n_recuperar(nodo)->clave == clave){
        altura_nario(nodo,1,altura);
        return;
    }

    NodoArbol hi = n_hijoizquierdo(nodo);
    NodoArbol hd = n_hijoderecho(nodo);

    buscar_nodo_nario(hi,clave,altura);
    buscar_nodo_nario(hd,clave,altura);
}

/*=======================================================================*/

void obtener_hermanos(NodoArbol nodo, int clave){
    if(ab_rama_nula(nodo)){
        return;
    }

    NodoArbol hijo = n_hijoizquierdo(nodo);
    while(!ab_rama_nula(hijo))
    {
        if(n_recuperar(hijo)->clave == clave){
            NodoArbol hermano = n_hijoizquierdo(nodo);
            printf("Hermanos de [%i] -> ",clave);

            while(!ab_rama_nula(hermano)){
                if(n_recuperar(hermano)->clave != clave){
                    printf("[%i] ",n_recuperar(hermano)->clave);
                }
                hermano = n_hijoderecho(hermano);
            }
            printf("\n");
            return;
        }
        obtener_hermanos(hijo,clave);
        hijo = n_hijoderecho(hijo);
    }
}

/*========================================================*/

int contar_hojas_nario(NodoArbol nodo){
    if(ab_rama_nula(nodo)){
        return 0;
    }

    NodoArbol hijo = n_hijoizquierdo(nodo);
    if(ab_rama_nula(hijo)){
        return 1;
    }

    int suma = 0;
    while(!ab_rama_nula(hijo)){
        suma += contar_hojas_nario(hijo);
        hijo = n_hijoderecho(hijo);
    }
    return suma;
}

/*===================================================*/

void hijos_raiz_nario(NodoArbol raiz){
    if(ab_rama_nula(raiz)){
        return;
    }

    NodoArbol hijo = n_hijoizquierdo(raiz);

    while(!ab_rama_nula(hijo)){
        printf("[%i] ",n_recuperar(hijo)->clave);
        hijo = n_hijoderecho(hijo);
    }
}

/*================================================*/

void hojas_mismo_nivel_nario(NodoArbol nodo, int nivel_actual, int* nivel, bool* mismo_nivel){
    if(ab_rama_nula(nodo)){
        return;
    }
    NodoArbol hijo = n_hijoizquierdo(nodo);

    if(ab_rama_nula(hijo)){
        if(*nivel == -1){
            *nivel = nivel_actual;
            return;
        }
        else{
            if(nivel_actual != *nivel){
                *mismo_nivel = false;
                return;
            }
        }
    }

    while(!ab_rama_nula(hijo))
    {
        hojas_mismo_nivel_nario(hijo,nivel_actual+1,nivel,mismo_nivel);
        hijo = n_hijoderecho(hijo);
    }
}

/*============================================================*/

void grado_nario(NodoArbol nodo, int* mas_hijos){
    if(ab_rama_nula(nodo)){
        return;
    }
    NodoArbol hijo = n_hijoizquierdo(nodo);
    int hijos_actual = 0;

    while(!ab_rama_nula(hijo)){
        hijos_actual++;
        grado_nario(hijo,mas_hijos);
        hijo = n_hijoderecho(hijo);
    }

    if(hijos_actual > *mas_hijos){
        *mas_hijos = hijos_actual;
    }
}

bool es_grado_k(ArbolBinario A, int grado){
    if(ab_esta_vacio(A)){
        return false;
    }
    int mas_hijos = 0;
    grado_nario(ab_raiz(A),&mas_hijos);
    return mas_hijos == grado;
}

/*================================================================*/

void imprimir_nivel_nario(NodoArbol nodo, int nivel_nodo, int nivel){
    if(ab_rama_nula(nodo)){
        return;
    }

    if(nivel_nodo == nivel){
        TipoElemento te = n_recuperar(nodo);
        printf("[%i] ",te->clave);
    }

    NodoArbol hijo = n_hijoizquierdo(nodo);
    while(!ab_rama_nula(hijo)){
        imprimir_nivel_nario(hijo,nivel_nodo+1,nivel);
        hijo = n_hijoderecho(hijo);
    }
}

/*=================================================================*/

void camino_raiz_nodo(NodoArbol nodo, int clave, Pila pila){
    if(ab_rama_nula(nodo)){
        return;
    }

    if(n_recuperar(nodo)->clave == clave){
        imprimir_ancestros(pila);
        return;
    }

    TipoElemento te = te_crear(n_recuperar(nodo)->clave);
    p_apilar(pila,te);

    NodoArbol hijo = n_hijoizquierdo(nodo);
    while(!ab_rama_nula(hijo)){
        camino_raiz_nodo(hijo,clave,pila);
        hijo = n_hijoderecho(hijo);
    }
    p_desapilar(pila);
}

/*==============================================================*/

void iterativo_anchura_nario(ArbolBinario A){
    if(ab_esta_vacio(A)){
        return;
    }

    Cola cola = c_crear();
    TipoElemento te_raiz = n_recuperar(ab_raiz(A));
    printf("Raiz -> [%i] ",te_raiz->clave);

    NodoArbol raiz_hi = n_hijoizquierdo(ab_raiz(A));
    if(ab_rama_nula(raiz_hi)){
        return;
    }

    TipoElemento te_actual,te_aux;
    TipoElemento te_hi = te_crear_con_valor(0,raiz_hi);
    c_encolar(cola,te_hi);

    while(!c_esta_vacia(cola)){
        te_actual = c_desencolar(cola);
        NodoArbol nodo_actual = (NodoArbol)(te_actual->valor);

        printf("[%i] ",n_recuperar(nodo_actual)->clave);

        NodoArbol hi = n_hijoizquierdo(nodo_actual);
        NodoArbol hd = n_hijoderecho(nodo_actual);

        if(!ab_rama_nula(hi)){
            te_aux = te_crear_con_valor(0,hi);
            c_encolar(cola,te_aux);
        }

        while(!ab_rama_nula(hd)){
            printf("[%i] ",n_recuperar(hd)->clave);

            NodoArbol hd_hijoiz = n_hijoizquierdo(hd);
            if(!ab_rama_nula(hd_hijoiz)){
                te_aux = te_crear_con_valor(0,hd_hijoiz);
                c_encolar(cola,te_aux);
            }
            hd = n_hijoderecho(hd);
        }
    }
}

/*=========================================================================*/

void nodos_internos_nario(ArbolBinario A, NodoArbol nodo, Lista lista){
    if(ab_rama_nula(nodo)){
        return;
    }

    NodoArbol hi = n_hijoizquierdo(nodo);
    NodoArbol hd = n_hijoderecho(nodo);

    if(!ab_rama_nula(hi) && nodo != ab_raiz(A)){
        TipoElemento te = n_recuperar(nodo);
        l_agregar(lista,te);
    }

    nodos_internos_nario(A,hi,lista);
    nodos_internos_nario(A,hd,lista);
}

Lista principal4(ArbolBinario A){
    Lista lista = l_crear();
    if(ab_esta_vacio(A)){
        return lista;
    }

    nodos_internos_nario(A,ab_raiz(A),lista);
    return lista;
}