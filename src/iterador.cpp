/* 5201305 */

#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/cadena.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_iterador
{
    TCadena coleccion;
    TLocalizador loc = NULL;
    bool reiniciado;
};

TIterador crearIterador()
{
    TIterador iterador = new _rep_iterador;
    iterador->coleccion = crearCadena();
    iterador->reiniciado = false;
    return iterador;
}

TIterador agregarAIterador(nat elem, TIterador iter)
{
    if (iter->reiniciado == false)
        insertarAlFinal(crearInfo(elem, 1), iter->coleccion);
    return iter;
}

TIterador reiniciarIterador(TIterador iter)
{
    if (!esVaciaCadena(iter->coleccion))
    {
        iter->loc = inicioCadena(iter->coleccion);
    }
    iter->reiniciado = true; //AGREGO
    return iter;
}

TIterador avanzarIterador(TIterador iter)
{
    if (estaDefinidaActual(iter))
    {
        iter->loc = siguiente(iter->loc, iter->coleccion);
    }
    return iter;
}

nat actualEnIterador(TIterador iter)
{
    assert(estaDefinidaActual(iter));
    return natInfo(infoCadena(iter->loc, iter->coleccion));
}

bool estaDefinidaActual(TIterador iter)
{
    return esLocalizador(iter->loc);
}

void liberarIterador(TIterador iter)
{
    liberarCadena(iter->coleccion);
    delete iter;
}