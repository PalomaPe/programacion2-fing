/*
  Módulo de definición de 'TColCadenas'.

  Un elemento de tipo 'TColCadenas' es una colección acotada de 'TCadena's.

  La cantidad de elementos que mantiene, M, se establece en el parámetro
  de 'crearColCadenas'.
  Cada cadena se identifica con una posición entre 0 y M - 1.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/usoTads.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_colCadenas
{
    TCadena *array;
    nat cota;
};

TColCadenas crearColCadenas(nat M)
{
    TColCadenas colCad = new _rep_colCadenas;
    colCad->array = new TCadena[M];
    colCad->cota = M;
    while (M > 0)
    {
        colCad->array[M - 1] = crearCadena();
        M--;
    }
    return colCad;
}

TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col)
{
    if (pos < col->cota)
    {
        if (esVaciaCadena(col->array[pos]))
            col->array[pos] = insertarAlFinal(info, col->array[pos]);
        else
            insertarAntes(info, inicioCadena(col->array[pos]), col->array[pos]);
    }
    return col;
}

bool estaEnColCadenas(nat dato, nat pos, TColCadenas col)
{
    return pertenece(dato, col->array[pos]);
}

TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col)
{
    return infoCadena(siguienteClave(dato, inicioCadena(col->array[pos]), col->array[pos]), col->array[pos]);
}

TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col)
{
    removerDeCadena(siguienteClave(dato, inicioCadena(col->array[pos]), col->array[pos]), col->array[pos]);
    return col;
}

void liberarColCadenas(TColCadenas col)
{
    int cota = col->cota - 1;
    while (cota >= 0)
    {
        liberarCadena(col->array[cota]);
        cota--;
    }
    delete[] col->array;
    delete col;
}
