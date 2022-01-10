/* 5201305 */
/*
  MÃ³dulo de implementadcÃ­on de 'colaBiarios.h'.
*/

#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/colaBinarios.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoC
{
    TBinario binario;
    nodoC *sig;
};

struct _rep_colaBinarios
{
    nodoC *inicio;
    nodoC *final;
};

TColaBinarios crearColaBinarios()
{
    TColaBinarios colaB = new _rep_colaBinarios;
    colaB->inicio = NULL;
    colaB->final = NULL;
    return colaB;
}

TColaBinarios encolar(TBinario b, TColaBinarios c)
{
    nodoC *nuevo = new nodoC;
    nuevo->binario = b;
    nuevo->sig = NULL;
    if (estaVaciaColaBinarios(c))
        c->inicio = nuevo;
    else
        c->final->sig = nuevo;
    c->final = nuevo;
    return c;
}

TColaBinarios desencolar(TColaBinarios c)
{
    if (!estaVaciaColaBinarios(c))
    {
        nodoC *nBorrar = c->inicio;
        c->inicio = nBorrar->sig;
        delete nBorrar;
    }
    return c;
}

void liberarColaBinarios(TColaBinarios c)
{
    while (!estaVaciaColaBinarios(c))
    {
        desencolar(c);
    }
    delete c;
}

bool estaVaciaColaBinarios(TColaBinarios c)
{
    return c->inicio == NULL;
}

TBinario frente(TColaBinarios c)
{
    assert(!estaVaciaColaBinarios(c));
    return c->inicio->binario;
}
