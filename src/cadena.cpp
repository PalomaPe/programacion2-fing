/* 5201305 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena
{
    TInfo dato;
    TLocalizador anterior;
    TLocalizador siguiente;
};

struct _rep_cadena
{
    TLocalizador inicio;
    TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena()
{
    TCadena res = new _rep_cadena;
    res->inicio = NULL;
    res->final = NULL;
    return res;
}

void liberarCadena(TCadena cad)
{
    while (esLocalizador(cad->inicio))
    {
        TLocalizador nodoBorrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(nodoBorrar->dato);
        delete nodoBorrar;
    }
    cad->final = NULL;
    delete cad;
}

bool esVaciaCadena(TCadena cad)
{
    return ((cad->inicio == NULL) && (cad->final == NULL));
}

TLocalizador inicioCadena(TCadena cad)
{
    /*
  // versión que sigue la especificación
    TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad->inicio;
    }
    return res;
  */

    // versión conociendo la implementación:
    // esVaciaCadena(cad) => cad->inicio == NUL
    assert(!esVaciaCadena(cad) || cad->inicio == NULL);
    return cad->inicio;
}

TLocalizador finalCadena(TCadena cad)
{
    TLocalizador res;
    if (esVaciaCadena(cad))
    {
        res = NULL;
    }
    else
    {
        res = cad->final;
    }
    return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    if (esFinalCadena(loc, cad))
    {
        return NULL;
    }
    else
    {
        return loc->siguiente;
    }
}

TLocalizador anterior(TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    if (esInicioCadena(loc, cad))
    {
        return NULL;
    }
    else
    {
        return loc->anterior;
    }
}

bool esFinalCadena(TLocalizador loc, TCadena cad)
{
    if (esVaciaCadena(cad))
    {
        return false;
    }
    else
    {
        return (loc == cad->final);
    };
}

bool esInicioCadena(TLocalizador loc, TCadena cad)
{
    if (esVaciaCadena(cad))
    {
        return false;
    }
    else
    {
        return (loc == cad->inicio);
    };
}

TCadena insertarAlFinal(TInfo i, TCadena cad)
{
    TLocalizador nodoNuevo = new nodoCadena;
    nodoNuevo->dato = i;
    if (esVaciaCadena(cad))
    {
        nodoNuevo->anterior = NULL;
        cad->inicio = nodoNuevo;
    }
    else
    {
        finalCadena(cad)->siguiente = nodoNuevo;
        nodoNuevo->anterior = finalCadena(cad);
    }
    nodoNuevo->siguiente = NULL;
    cad->final = nodoNuevo;
    nodoNuevo = NULL;
    return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    TLocalizador nodoNuevo = new nodoCadena;
    nodoNuevo->dato = i;
    if (esInicioCadena(loc, cad))
    {
        nodoNuevo->anterior = NULL;
        cad->inicio = nodoNuevo;
    }
    else
    {
        loc->anterior->siguiente = nodoNuevo;
        nodoNuevo->anterior = loc->anterior;
    }
    loc->anterior = nodoNuevo;
    nodoNuevo->siguiente = loc;
    return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    if (esInicioCadena(loc, cad) || esFinalCadena(loc, cad))
    {
        if ((esInicioCadena(loc, cad)) && esFinalCadena(loc, cad))
        {
            cad->inicio = NULL;
            cad->final = NULL;
        }
        else if (esFinalCadena(loc, cad))
        {
            loc->anterior->siguiente = NULL;
            cad->final = loc->anterior;
        }
        else
        {
            loc->siguiente->anterior = NULL;
            cad->inicio = loc->siguiente;
        }
    }
    else
    {
        loc->anterior->siguiente = loc->siguiente;
        loc->siguiente->anterior = loc->anterior;
    }
    liberarInfo(loc->dato);
    loc->anterior = NULL;
    loc->siguiente = NULL;
    delete loc;
    return cad;
}

void imprimirCadena(TCadena cad)
{
    if (!esVaciaCadena(cad))
    {
        TLocalizador nodo = cad->inicio;
        while (nodo != NULL)
        {
            ArregloChars txt = infoATexto(nodo->dato);
            printf("%s", txt);
            delete[] txt;
            nodo = nodo->siguiente;
        }
    }
    printf("\n");
}

TLocalizador kesimo(nat k, TCadena cad)
{
    if (k == 0)
    {
        return NULL;
    }
    else
    {
        nat contador = 1;
        TLocalizador nodo = cad->inicio;
        while (nodo != NULL && contador < k)
        {
            nodo = nodo->siguiente;
            contador++;
        }
        if (contador == k)
        {
            TLocalizador loc = nodo;
            return loc;
        }
        else
        {
            return NULL;
        }
    }
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad) || esVaciaCadena(cad));
    if (!esVaciaCadena(sgm))
    {
        if (esVaciaCadena(cad))
        {
            cad->inicio = sgm->inicio;
            cad->final = sgm->final;
        }
        else
        {
            if (esFinalCadena(loc, cad))
            {
                loc->siguiente = sgm->inicio;
                sgm->inicio->anterior = loc;
                cad->final = sgm->final;
            }
            else
            {
                loc->siguiente->anterior = sgm->final;
                sgm->final->siguiente = loc->siguiente;
                loc->siguiente = sgm->inicio;
                sgm->inicio->anterior = loc;
            }
        }
    }
    sgm->inicio = NULL;
    sgm->final = NULL;
    delete sgm;
    return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad)
{
    assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
    TCadena cadSegmento = crearCadena();
    while (precedeEnCadena(desde, hasta, cad))
    {
        insertarAlFinal(copiaInfo(desde->dato), cadSegmento);
        desde = desde->siguiente;
    }
    return cadSegmento;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad)
{
    assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
    while (precedeEnCadena(desde, hasta, cad))
    {
        TLocalizador desdeNodo = desde->siguiente;
        removerDeCadena(desde, cad);
        desde = desdeNodo;
    }
    return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    loc->dato = i;
    return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad)
{
    assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
    TInfo aux = loc1->dato;
    cambiarEnCadena(loc2->dato, loc1, cad);
    cambiarEnCadena(aux, loc2, cad);
    return cad;
}

/*bool localizadorEnCadena(TLocalizador loc, TCadena cad)
{
    bool res;
    if (esVaciaCadena(cad))
    {
        res = false;
    }
    else
    {
        TLocalizador punteroANodo = cad->inicio;
        while (esLocalizador(punteroANodo) && loc != punteroANodo)
        {
            punteroANodo = punteroANodo->siguiente;
        }
        res = esLocalizador(punteroANodo);
        punteroANodo = NULL; //delete?
    }
    return res;
}*/

bool localizadorEnCadena(TLocalizador loc, TCadena cad){
    bool res = false;
    if (!esVaciaCadena(cad)) {
        TLocalizador locAux = inicioCadena(cad);
        while (!esFinalCadena(locAux, cad) && (locAux != loc)) {
                locAux = siguiente(locAux, cad);
        }
        res = (loc == locAux);
    }
    
    return res;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad)
{
    if (esVaciaCadena(cad))
    {
        return false;
    }
    else
    {
        bool res;
        if (localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad))
        {
            TLocalizador punteroANodo = cad->inicio;
            while (esLocalizador(punteroANodo) && (loc1 != punteroANodo && loc2 != punteroANodo))
            {
                punteroANodo = punteroANodo->siguiente;
            }
            if (esLocalizador(punteroANodo))
            {
                res = (loc1 == punteroANodo);
            }
            punteroANodo = NULL;
        }
        else
        {
            res = false;
        }
        return res;
    }
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad)
{
    assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
    while (esLocalizador(loc) && natInfo(loc->dato) != clave)
    {
        loc = loc->siguiente;
    }
    if (esLocalizador(loc))
    {
        return loc;
    }
    else
        return NULL;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad)
{
    assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
    while (esLocalizador(loc) && natInfo(loc->dato) != clave)
    {
        loc = loc->anterior;
    }
    if (esLocalizador(loc))
    {
        return loc;
    }
    else
        return NULL;
}

TLocalizador menorEnCadenaAux(TLocalizador puntero, nat menor)
{
    TLocalizador res;
    if (puntero == NULL)
    {
        res = puntero->anterior;
    }
    else
    {
        if (menor > natInfo(puntero->dato))
        {
            menor = natInfo(puntero->dato);
            puntero = puntero->siguiente;
        };
        res = menorEnCadenaAux(puntero, menor);
    }
    return res;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad)
{
    assert(localizadorEnCadena(loc, cad));
    nat natMenor = natInfo(loc->dato);
    TLocalizador menorLoc = loc;
    while (esLocalizador(loc->siguiente))
    {
        if (natMenor > natInfo(loc->siguiente->dato))
        {
            natMenor = natInfo(loc->siguiente->dato);
            menorLoc = loc->siguiente;
        }
        loc = loc->siguiente;
    }
    return menorLoc;
}
