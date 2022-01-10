#include "../include/conjunto.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/usoTads.h"
#include "../include/avl.h"
#include "../include/iterador.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_conjunto
{
    TAvl avl;
    nat min;
    nat max;
};

TConjunto crearConjunto()
{
    return NULL;
}

TConjunto singleton(nat elem)
{
    TConjunto conj = new _rep_conjunto;
    conj->avl = crearAvl();
    conj->avl = insertarEnAvl(elem, conj->avl);
    conj->min = elem;
    conj->max = elem;
    return conj;
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2)
{
    TConjunto conUnion;
    if (!estaVacioConjunto(c1) || !estaVacioConjunto(c2))
    {
        TIterador iter1 = iteradorDeConjunto(c1);
        TIterador iter2 = iteradorDeConjunto(c2);
        TIterador iterUnion = enAlguno(iter1, iter2);
        liberarIterador(iter1);
        liberarIterador(iter2);
        iterUnion = reiniciarIterador(iterUnion);
        nat largoIter = cantidadEnIterador(iterUnion);
        ArregloNats arrUnion = new nat[largoIter];
        int i = 0;
        if (largoIter > 0)
        {
            iterUnion = reiniciarIterador(iterUnion);
            while (estaDefinidaActual(iterUnion))
            {
                arrUnion[i] = actualEnIterador(iterUnion);
                iterUnion = avanzarIterador(iterUnion);
                i++;
            }
            conUnion = arregloAConjunto(arrUnion, cantidadEnIterador(iterUnion));
            liberarIterador(iterUnion);
            delete[] arrUnion;
        }
    }
    else
    {
        conUnion = crearConjunto();
    }
    /*else if (!estaVacioConjunto(c1))
    {
        TIterador iter1 = iteradorDeConjunto(c1);
        ArregloNats arrUnion = new nat[cantidadEnIterador(iter1)];
        int i = 0;
        iter1 = reiniciarIterador(iter1);
        while (estaDefinidaActual(iter1))
        {
            arrUnion[i] = actualEnIterador(iter1);
            iter1 = avanzarIterador(iter1);
            i++;
        }
        conUnion = arregloAConjunto(arrUnion, cantidadEnIterador(iter1));
        liberarIterador(iter1);
        delete[] arrUnion;
    }
    else if (!estaVacioConjunto(c2))
    {
        TIterador iter2 = iteradorDeConjunto(c2);
        ArregloNats arrUnion = new nat[cantidadEnIterador(iter2)];
        int i = 0;
        iter2 = reiniciarIterador(iter2);
        while (estaDefinidaActual(iter2))
        {
            arrUnion[i] = actualEnIterador(iter2);
            iter2 = avanzarIterador(iter2);
            i++;
        }
        conUnion = arregloAConjunto(arrUnion, cantidadEnIterador(iter2));
        liberarIterador(iter2);
        delete[] arrUnion;
    }*/
    return conUnion;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2)
{
    TConjunto conDiferencia = NULL;
    if (!estaVacioConjunto(c1))
    {
        TIterador iter1 = iteradorDeConjunto(c1);
        TIterador iter2 = iteradorDeConjunto(c2);
        TIterador iterDiferencia = soloEnA(iter1, iter2);
        liberarIterador(iter1);
        liberarIterador(iter2);
        nat largoIter = cantidadEnIterador(iterDiferencia);
        if (largoIter > 0)
        {
            ArregloNats arrDiferencia = new nat[largoIter];
            int i = 0;
            iterDiferencia = reiniciarIterador(iterDiferencia);
            while (estaDefinidaActual(iterDiferencia))
            {
                arrDiferencia[i] = actualEnIterador(iterDiferencia);
                iterDiferencia = avanzarIterador(iterDiferencia);
                i++;
            }
            conDiferencia = arregloAConjunto(arrDiferencia, cantidadEnIterador(iterDiferencia));
            delete[] arrDiferencia;
        }
        liberarIterador(iterDiferencia);
    }
    else
    {
        conDiferencia = crearConjunto();
    }
    /*else if (!estaVacioConjunto(c1))
    {
        TIterador iter1 = iteradorDeConjunto(c1);
        ArregloNats arrDiferencia = new nat[cantidadEnIterador(iter1)];
        int i = 0;
        iter1 = reiniciarIterador(iter1);
        while (estaDefinidaActual(iter1))
        {
            arrDiferencia[i] = actualEnIterador(iter1);
            iter1 = avanzarIterador(iter1);
            i++;
        }
        conDiferencia = arregloAConjunto(arrDiferencia, cantidadEnIterador(iter1));
        liberarIterador(iter1);
        delete[] arrDiferencia;
    }*/
    return conDiferencia;
}

bool perteneceAConjunto(nat elem, TConjunto c)
{
    if (!estaVacioConjunto(c))
    {
        return !estaVacioAvl(buscarEnAvl(elem, c->avl));
    }
    else
        return false;
}

bool estaVacioConjunto(TConjunto c)
{
    return c == NULL;
}

nat cardinalidad(TConjunto c)
{
    if (!estaVacioConjunto(c))
        return cantidadEnAvl(c->avl);
    else
        return 0;
}

nat minimo(TConjunto c)
{
    assert(!estaVacioConjunto(c));
    return c->min;
}

nat maximo(TConjunto c)
{
    assert(!estaVacioConjunto(c));
    return c->max;
}

TConjunto arregloAConjunto(ArregloNats elems, nat n)
{
    assert(n > 0);
    TConjunto c = new _rep_conjunto;
    c->avl = arregloAAvl(elems, n);
    c->min = elems[0];
    c->max = elems[n - 1];
    return c;
}

TIterador iteradorDeConjunto(TConjunto c)
{
    if (!estaVacioConjunto(c))
        return enOrdenAvl(c->avl);
    else
        return crearIterador();
}

void liberarConjunto(TConjunto c)
{
    if (!estaVacioConjunto(c))
        liberarAvl(c->avl);
    delete c;
}