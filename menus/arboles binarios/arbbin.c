#include "arbbin.h"

void f_recursiva1(NodoArbol actual, int nivel, int nivel_actual){
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

    f_recursiva1(hi,nivel,nivel_actual+1);
    f_recursiva1(hd,nivel,nivel_actual+1);
}