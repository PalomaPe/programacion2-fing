/* 5201305 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"
#include "../include/binario.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"
#include "../include/avl.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <limits.h>

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2)
{
    TConjunto cInterseccion = crearConjunto();
    if (!estaVacioConjunto(c1) && !estaVacioConjunto(c2))
    {
        TConjunto c1SinC2 = diferenciaDeConjuntos(c1, c2);
        //TConjunto soloEnC2 = diferenciaDeConjuntos(c2, c1);
        //TConjunto unionDiferenciaC1C2 = unionDeConjuntos(soloEnC1, soloEnC2);
        //TConjunto unionC1C2 = unionDeConjuntos(c1, c2);
        
        //liberarConjunto(soloEnC2);
        cInterseccion = diferenciaDeConjuntos(c1, c1SinC2);
        liberarConjunto(c1SinC2);
        //liberarConjunto(unionC1C2);
        //liberarConjunto(unionDiferenciaC1C2);
    }
    return cInterseccion;
}

nat cantidadEnIterador(TIterador it)
{
    reiniciarIterador(it);
    int contador = 0;
    while (estaDefinidaActual(it))
    {
        avanzarIterador(it);
        contador++;
    }
    return contador;
}

TIterador enAlguno(TIterador a, TIterador b)
{
    reiniciarIterador(a);
    reiniciarIterador(b);
    TIterador enAlgunoIter = crearIterador();
    while ((estaDefinidaActual(a) || estaDefinidaActual(b)))
    {
        if (estaDefinidaActual(a) && estaDefinidaActual(b))
        {
            nat actualA = actualEnIterador(a);
            nat actualB = actualEnIterador(b);
            if (actualA < actualB)
            {
                agregarAIterador(actualA, enAlgunoIter);
                avanzarIterador(a);
            }
            else if (actualA > actualB)
            {
                agregarAIterador(actualB, enAlgunoIter);
                avanzarIterador(b);
            }
            else
            {
                agregarAIterador(actualA, enAlgunoIter);
                avanzarIterador(a);
                avanzarIterador(b);
            }
        }
        else if (estaDefinidaActual(a))
        {
            agregarAIterador(actualEnIterador(a), enAlgunoIter);
            avanzarIterador(a);
        }
        else if (estaDefinidaActual(b))
        {
            agregarAIterador(actualEnIterador(b), enAlgunoIter);
            avanzarIterador(b);
        }
    }
    return enAlgunoIter;
}

TIterador soloEnA(TIterador a, TIterador b)
{
    reiniciarIterador(a);
    reiniciarIterador(b);
    TIterador soloEnAIter = crearIterador();
    while (estaDefinidaActual(a))
    {
        nat actualEnA = actualEnIterador(a);
        if (estaDefinidaActual(b))
        {
            if (actualEnA < actualEnIterador(b))
            {
                agregarAIterador(actualEnA, soloEnAIter);
                avanzarIterador(a);
            }
            else if (actualEnA > actualEnIterador(b))
            {
                avanzarIterador(b);

            }
            else
            {
                avanzarIterador(a);
                avanzarIterador(b);
            }
        }
        else
        {
            agregarAIterador(actualEnA, soloEnAIter);
            avanzarIterador(a);
        }
    }
    return soloEnAIter;
}

TIterador recorridaPorNiveles(TBinario b)
{
    TIterador iter = crearIterador();
    if (b != NULL)
    {
        TPila p = crearPila(alturaBinario(b) + cantidadBinario(b));
        TColaBinarios c = crearColaBinarios();
        c = encolar(b, c);
        c = encolar(NULL, c);
        while (!estaVaciaColaBinarios(c))
        {
            b = frente(c);
            c = desencolar(c);
            if (b == NULL && !estaVaciaColaBinarios(c))
            {
                c = encolar(NULL, c);
            }
            if (b == NULL)
                p = apilar(UINT_MAX, p);
            else
            {
                p = apilar(natInfo(raiz(b)), p);
                if (derecho(b) != NULL)
                {
                    c = encolar(derecho(b), c);
                }
                if (izquierdo(b) != NULL)
                {
                    c = encolar(izquierdo(b), c);
                }
            }
        }
        liberarColaBinarios(c);
        p = desapilar(p);
        while (!estaVaciaPila(p))
        {
            iter = agregarAIterador(cima(p), iter);
            p = desapilar(p);
        }
        liberarPila(p);
    }
    return iter;
}

void nivelEnBinarioAux(nat contador, TCadena cad, nat l, TBinario b)
{
    if (b != NULL)
    {
        if (contador == l)
        {
            insertarAlFinal(copiaInfo(raiz(b)), cad);
        }
        contador++;
        nivelEnBinarioAux(contador, cad, l, izquierdo(b));
        nivelEnBinarioAux(contador, cad, l, derecho(b));
    }
}

TCadena nivelEnBinario(nat l, TBinario b)
{
    nat contador = 1;
    TCadena cadenaNivel = crearCadena();
    if (b != NULL && l <= alturaBinario(b))
    {
        nivelEnBinarioAux(contador, cadenaNivel, l, b);
        return cadenaNivel;
    }
    else
        return cadenaNivel;
}

bool esCamino(TCadena c, TBinario b)
{
    nat largoCad = longitud(c);
    TLocalizador loc = inicioCadena(c);
    if (largoCad <= alturaBinario(b) && b != NULL)
    {
        while (b != NULL && loc != NULL && (natInfo(raiz(b)) == natInfo(infoCadena(loc, c))))
        {
            if (siguiente(loc, c) != NULL)
            {
                loc = siguiente(loc, c);
                if (izquierdo(b) == NULL || (natInfo(raiz(izquierdo(b))) == natInfo(infoCadena(loc, c))))
                {
                    b = izquierdo(b);
                }
                else if (derecho(b) == NULL || (natInfo(raiz(derecho(b))) == natInfo(infoCadena(loc, c))))
                {
                    b = derecho(b);
                }
                else
                    return false;
            }
            else
                return izquierdo(b) == NULL && derecho(b) == NULL;
        }
        return (b == NULL || (derecho(b) == NULL && izquierdo(b) == NULL)) && (loc == NULL);
    }
    else if (largoCad == 0 && b == NULL)
        return true;
    else
        return false;
}

bool pertenece(nat elem, TCadena cad)
{
    if (!esVaciaCadena(cad))
    {
        TLocalizador nodo = inicioCadena(cad);
        while (esLocalizador(siguiente(nodo, cad)) && natInfo(infoCadena(nodo, cad)) != elem)
        {
            nodo = siguiente(nodo, cad);
        }
        return natInfo(infoCadena(nodo, cad)) == elem;
    }
    else
    {
        return false;
    }
}

nat longitud(TCadena cad)
{
        int contador = 0;
        TLocalizador nodo = inicioCadena(cad);
        while (nodo != NULL)
        {
            contador++;
            nodo = siguiente(nodo, cad);
        }
        nodo = NULL;
        return contador;
}

bool estaOrdenadaPorNaturales(TCadena cad)
{
    bool res;
    if (esVaciaCadena(cad))
    {
        res = true;
    }
    else
    {
        TLocalizador nodo = inicioCadena(cad);
        while (esLocalizador(siguiente(nodo, cad)) && natInfo(infoCadena(nodo, cad)) <= natInfo(infoCadena(siguiente(nodo, cad), cad)))
        {
            nodo = siguiente(nodo, cad);
        }
        if (!esLocalizador(siguiente(nodo, cad)))
        {
            res = true;
        }
        else
        {
            res = false;
        }
        nodo = NULL;
    }
    return res;
}

bool hayNatsRepetidos(TCadena cad)
{
    if (!esVaciaCadena(cad))
    {
        TLocalizador loc1 = inicioCadena(cad);
        bool res = false;
        while (esLocalizador(loc1) && !res)
        {
            nat natural = natInfo(infoCadena(loc1, cad));
            TLocalizador loc2 = inicioCadena(cad);
            while (esLocalizador(loc2) && !res)
            {
                if (esInicioCadena(loc1, cad) || esFinalCadena(loc1, cad))
                {
                    if (esInicioCadena(loc1, cad))
                    {
                        res = siguienteClave(natural, siguiente(loc1, cad), cad) != NULL;
                    }
                    else
                    {
                        res = anteriorClave(natural, anterior(loc1, cad), cad) != NULL;
                    }
                }
                else
                {
                    res = (siguienteClave(natural, siguiente(loc1, cad), cad) != NULL || anteriorClave(natural, anterior(loc1, cad), cad) != NULL);
                }
                loc2 = siguiente(loc2, cad);
            }
            loc1 = siguiente(loc1, cad);
        }
        return res;
    }
    else
    {
        return false;
    }
}

bool sonIgualesCadena(TCadena c1, TCadena c2)
{
    if (esVaciaCadena(c1) && esVaciaCadena(c2))
    {
        return true;
    }
    else
    {
        TLocalizador nodoC1 = inicioCadena(c1);
        TLocalizador nodoC2 = inicioCadena(c2);
        while ((esLocalizador(nodoC1) && esLocalizador(nodoC2)) && sonIgualesInfo(infoCadena(nodoC1, c1), infoCadena(nodoC2, c1)))
        {
            nodoC1 = siguiente(nodoC1, c1);
            nodoC2 = siguiente(nodoC2, c2);
        }
        return (nodoC1 == NULL && nodoC2 == NULL);
    }
}

TCadena concatenar(TCadena c1, TCadena c2)
{
    if (esVaciaCadena(c1) && esVaciaCadena(c2))
    {
        TCadena cadVacia = crearCadena();
        return cadVacia;
    }
    else
    {
        TLocalizador desdeC1 = inicioCadena(c1);
        TLocalizador hastaC1 = finalCadena(c1);
        TLocalizador desdeC2 = inicioCadena(c2);
        TLocalizador hastaC2 = finalCadena(c2);
        TCadena copiaC1 = copiarSegmento(desdeC1, hastaC1, c1);
        TCadena copiaC2 = copiarSegmento(desdeC2, hastaC2, c2);
        copiaC1 = insertarSegmentoDespues(copiaC2, finalCadena(copiaC1), copiaC1);
        return copiaC1;
    }
}

TCadena ordenar(TCadena cad)
{
    assert(!hayNatsRepetidos(cad));
    if (!esVaciaCadena(cad))
    {
        TLocalizador nodoExterno = inicioCadena(cad);
        while (esLocalizador(nodoExterno))
        {
            TLocalizador nodoInterno = inicioCadena(cad);
            while (esLocalizador(nodoInterno))
            {
                if (esLocalizador(siguiente(nodoInterno, cad)) && (natInfo(infoCadena(nodoInterno, cad)) > natInfo(infoCadena(siguiente(nodoInterno, cad), cad))))
                {
                    intercambiar(nodoInterno, siguiente(nodoInterno, cad), cad);
                }
                nodoInterno = siguiente(nodoInterno, cad);
            }
            nodoExterno = siguiente(nodoExterno, cad);
        }
    }
    return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad)
{
    TLocalizador nodo = inicioCadena(cad);
    while (esLocalizador(nodo))
    {
        if (natInfo(infoCadena(nodo, cad)) == original)
        {
            TInfo nuevoInfo = crearInfo(nuevo, realInfo(infoCadena(nodo, cad)));
            TInfo viejoInfo = infoCadena(nodo, cad);
            cambiarEnCadena(nuevoInfo, nodo, cad);
            liberarInfo(viejoInfo);
        }
        nodo = siguiente(nodo, cad);
    }
    return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad)
{
    assert(estaOrdenadaPorNaturales(cad) && menor <= mayor &&
           pertenece(menor, cad) &&
           pertenece(mayor, cad));
    TCadena subcadenaRes = crearCadena();
    TLocalizador nodoCad = inicioCadena(cad);
    while (esLocalizador(nodoCad))
    {
        if (menor <= natInfo(infoCadena(nodoCad, cad)) && natInfo(infoCadena(nodoCad, cad)) <= mayor)
        {
            TInfo valorIntermedio = copiaInfo(infoCadena(nodoCad, cad));
            insertarAlFinal(valorIntermedio, subcadenaRes);
        }
        nodoCad = siguiente(nodoCad, cad);
    }
    return subcadenaRes;
}