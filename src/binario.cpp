/* 5201305 */
/*
  MÃ³dulo de implementadcÃ­on de 'TBinario'.
*/

#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/avl.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_binario
{
    TBinario left;
    TBinario right;
    TInfo dato;
};

TBinario avlABinarioAux(TAvl a, TBinario &b)
{
    if (a != NULL) {
        b = insertarEnBinario(crearInfo(raizAvl(a), 0), b);
        b = avlABinarioAux(izqAvl(a), b);
        b = avlABinarioAux(derAvl(a), b);
    }
    return b;
}

TBinario avlABinario(TAvl a)
{
    TBinario b = crearBinario();
    return avlABinarioAux(a, b);
}

TBinario insertarEnBinarioSA(TInfo i, TBinario &b)
{
    if (b == NULL)
    {
        b = new _rep_binario;
        b->dato = i;
        b->left = b->right = NULL;
    }
    else if (natInfo(i) < natInfo(b->dato))
    {
        insertarEnBinarioSA(i, b->left);
    }
    else if (natInfo(i) > natInfo(b->dato))
    {
        insertarEnBinarioSA(i, b->right);
    }
    return b;
}

TBinario binarioBalanceadoAux(ArregloNats elems, int inicio, int final, TBinario bB, nat tam)
{
    if (final >= 0 && inicio < final)
    {
        nat pos = (final - 1 + inicio) / 2;
        bB = insertarEnBinarioSA(crearInfo(elems[pos], 0), bB);
        binarioBalanceadoAux(elems, inicio, pos, bB, tam);
        binarioBalanceadoAux(elems, pos + 1, final, bB, tam);
    }
    return bB;
}

TBinario binarioBalanceado(ArregloNats elems, nat n)
{
    TBinario bB = crearBinario();
    if (n > 0)
        bB = binarioBalanceadoAux(elems, 0, n, bB, n);
    return bB;
}

TBinario crearBinario()
{
    return NULL;
}

void insertarEnBinarioAux(TInfo i, TBinario &b)
{
    if (b == NULL)
    {
        b = new _rep_binario;
        b->dato = i;
        b->left = b->right = NULL;
    }
    else if (natInfo(i) < natInfo(b->dato))
    {
        insertarEnBinarioAux(i, b->left);
    }
    else if (natInfo(i) > natInfo(b->dato))
    {
        insertarEnBinarioAux(i, b->right);
    }
}

TBinario insertarEnBinario(TInfo i, TBinario b)
{
    assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));
    insertarEnBinarioAux(i, b);
    return b;
}

TInfo mayor(TBinario b)
{
    assert(!esVacioBinario(b));
    while (b->right != NULL)
    {
        b = b->right;
    }
    return b->dato;
}

void removerMayorAux(TBinario &b)
{
    if (b->dato == mayor(b))
    {
        if (b->left != NULL)
        {
            TBinario aux = b;
            b = b->left;
            aux->left = NULL;
            aux->dato = NULL;
            delete aux;
        }
        else
        {
            b->dato = NULL;
            delete b;
            b = NULL;
        }
    }
    else
        removerMayorAux(b->right);
}

TBinario removerMayor(TBinario b)
{
    assert(!esVacioBinario(b));
    removerMayorAux(b);
    return b;
}

void removerDeBinarioAux(nat elem, TBinario &b)
{
    if (b != NULL)
    {
        if (elem < natInfo(b->dato))
            removerDeBinarioAux(elem, b->left);
        else if (elem > natInfo(b->dato))
            removerDeBinarioAux(elem, b->right);
        else
        {
            //clave == t->key
            liberarInfo(b->dato);
            if (b->left == NULL && b->right == NULL)
            {
                delete b;
                b = NULL;
            }
            else
            {
                if (b->right == NULL)
                {
                    TBinario aux = b;
                    b = b->left;
                    aux->left = aux->right = NULL;
                    delete aux;
                }
                else if (b->left == NULL)
                {
                    TBinario aux = b;
                    b = b->right;
                    aux->left = aux->right = NULL;
                    delete aux;
                }
                else
                {
                    b->dato = mayor(b->left);
                    removerMayorAux(b->left);
                }
            }
        }
    }
}

TBinario removerDeBinario(nat elem, TBinario b)
{
    assert(!esVacioBinario(buscarSubarbol(elem, b)));
    removerDeBinarioAux(elem, b);
    return b;
}

void liberarBinario(TBinario b)
{
    if (b != NULL)
    {
        liberarBinario(b->left);
        liberarBinario(b->right);
        liberarInfo(b->dato);
        delete b;
    }
    else
        delete b;
}

bool esVacioBinario(TBinario b)
{
    return (b == NULL);
}

nat valorAbs(nat a, nat b)
{
    if (a >= b)
        return (a - b);
    else
        return -(a - b);
}

bool esAvlAux(TBinario binario, bool &esAVL)
{
    if (esAVL)
    {
        if (binario != NULL)
        {
            if (binario->left != NULL || binario->right != NULL)
            {
                if (valorAbs(alturaBinario(binario->left), alturaBinario(binario->right)) > 1)
                {
                    esAVL = false;
                }
                else
                    esAVL = (esAvlAux(binario->left, esAVL) && esAvlAux(binario->right, esAVL));
            }
            else
                esAVL = true;
        }
        else
            esAVL = true;
    }
    return esAVL;
}

bool esAvl(TBinario b)
{
    if (b != NULL)
    {
        if (b->left != NULL || b->right != NULL)
        {
            bool esAVL = true;
            return esAvlAux(b, esAVL);
        }
        else
            return true;
    }
    else
        return true;
}

TInfo raiz(TBinario b)
{
    assert(!esVacioBinario(b));
    return b->dato;
}

TBinario izquierdo(TBinario b)
{
    assert(!esVacioBinario(b));
    return b->left;
}

TBinario derecho(TBinario b)
{
    assert(!esVacioBinario(b));
    return b->right;
}

TBinario buscarSubarbol(nat elem, TBinario b)
{
    if (b != NULL)
    {
        while (b != NULL && natInfo(b->dato) != elem)
        {
            if (natInfo(b->dato) > elem)
                b = b->left;
            else
                b = b->right;
        }
    }
    return b;
}

nat alturaBinario(TBinario b)
{
    if (b == NULL)
        return 0;
    else
    {
        nat alturaLeft = alturaBinario(b->left);
        nat alturaRight = alturaBinario(b->right);
        if (alturaLeft >= alturaRight)
            return alturaLeft + 1;
        else
            return alturaRight + 1;
    }
}

nat cantidadBinario(TBinario b)
{
    if (b == NULL)
        return 0;
    else
        return 1 + cantidadBinario(b->left) + cantidadBinario(b->right);
}

void sumaUltimosPositivosAux(nat i, nat &contador, double &suma, TBinario b)
{
    if (b != NULL)
    {
        //if (contador <= i)
        //{
        sumaUltimosPositivosAux(i, contador, suma, b->right);
        //}
        if ((realInfo(b->dato) > 0) && contador <= i)
        {
            contador = contador + 1;
            suma = suma + realInfo(b->dato);
        }
        //if (contador <= i)
        //{
        sumaUltimosPositivosAux(i, contador, suma, b->left);
        //}
    }
}

double sumaUltimosPositivos(nat i, TBinario b)
{
    nat contador = 1;
    double suma = 0;
    if (b != NULL)
    {
        sumaUltimosPositivosAux(i, contador, suma, b);
        return suma;
    }
    else
        return 0;
}

TCadena linealizacionAux(TCadena &cad, TBinario b)
{
    if (b != NULL)
    {
        linealizacionAux(cad, b->left);
        insertarAlFinal(copiaInfo(b->dato), cad);
        linealizacionAux(cad, b->right);
    }
    return cad;
}

TCadena linealizacion(TBinario b)
{
    TCadena cadLineal = crearCadena();
    if (b != NULL)
    {
        linealizacionAux(cadLineal, b);
    }
    return cadLineal;
}

TInfo mayorMenor(double cota, TInfo noMenor, TBinario b)
{
    if (b != NULL && noMenor != NULL)
    {
        mayorMenor(cota, noMenor, b->right);
        if (realInfo(b->dato) < cota && realInfo(noMenor) < realInfo(b->dato))
            noMenor = b->dato;
        mayorMenor(cota, noMenor, b->left);
    }
    return noMenor;
}

TInfo menorMenor(double cota, TInfo noMenor, TBinario b)
{
    if (b != NULL && noMenor != NULL)
    {
        menorMenor(cota, noMenor, b->left);
        if (realInfo(b->dato) < cota && realInfo(noMenor) < realInfo(b->dato))
            noMenor = b->dato;
        menorMenor(cota, noMenor, b->right);
    }
    return noMenor;
}

TBinario menoresAux(double cota, TBinario b, TBinario &bFiltrado)
{
    if (b != NULL)
    {
        if (realInfo(b->dato) < cota)
            bFiltrado = insertarEnBinario(copiaInfo(b->dato), bFiltrado);
        else
        {
            if (mayorMenor(cota, b->dato, b->left) != b->dato)
            {
                bFiltrado = insertarEnBinario(copiaInfo(mayorMenor(cota, b->dato, b->left)), bFiltrado);
            }
            else if (mayorMenor(cota, b->dato, b->right) != b->dato)
                bFiltrado = insertarEnBinario(copiaInfo(menorMenor(cota, b->dato, b->right)), bFiltrado);
        }
        bFiltrado = menoresAux(cota, b->left, bFiltrado);
        bFiltrado = menoresAux(cota, b->right, bFiltrado);
    }
    return bFiltrado;
}

TBinario menores(double cota, TBinario b)
{
    if (b != NULL)
    {
        TBinario bFiltradoPorCota = crearBinario();
        return menoresAux(cota, b, bFiltradoPorCota);
    }
    else
        return NULL;
}

nat profundidad(TInfo datoP, TBinario b)
{
    nat profundidad = 0;
    while (datoP != b->dato)
    {
        profundidad++;
        if (natInfo(b->dato) > natInfo(datoP))
            b = b->left;
        else
            b = b->right;
    }
    return profundidad;
}

void imprimirBinarioAux(TBinario b, TBinario cB)
{
    if (b != NULL)
    {
        imprimirBinarioAux(b->right, cB);
        for (nat i = 0; i < profundidad(b->dato, cB); i++)
        {
            printf("%s", "-");
        }
        ArregloChars txtArb = infoATexto(b->dato);
        printf("%s\n", txtArb);
        delete[] txtArb;
        imprimirBinarioAux(b->left, cB);
    }
}

void imprimirBinario(TBinario b)
{
    printf("\n");
    if (b != NULL)
    {
        TBinario copiaB = b;
        imprimirBinarioAux(b, copiaB);
        copiaB = NULL;
    }
}