/* 5201305 */
/*
  MÃ³dulo de implementadcÃ­on de 'TPila'.
*/

#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/pila.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_pila
{
    int *array;
    int tope;
    int cota;
};

TPila crearPila(nat tamanio)
{
    TPila p = new _rep_pila;
    p->tope = 0;
    p->array = new int[tamanio];
    p->cota = tamanio;
    return p;
}

TPila apilar(nat num, TPila p)
{
    if (!estaLlenaPila(p))
    {
        p->array[p->tope] = num;
        p->tope = p->tope + 1;
    }
    return p;
}

TPila desapilar(TPila p)
{
    if (!estaVaciaPila(p))
    {
        p->tope = p->tope - 1;
    }
    return p;
}

void liberarPila(TPila p)
{
    delete[] p->array;
    delete p;
}

bool estaVaciaPila(TPila p) { return p->tope == 0; }

bool estaLlenaPila(TPila p) { return p->tope == p->cota; }

nat cima(TPila p)
{
    if (p->tope != 0)
    {
        return p->array[p->tope - 1];
    }
    else
        return 0;
}
