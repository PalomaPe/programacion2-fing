/*
  MÃƒÂ³dulo de implementaciÃƒÂ³n de 'TAvl'.

  Los elementos de tipo 'TAvl' son avls cuyos elementos son de tipo nat.

  Laboratorio de ProgramaciÃƒÂ³n 2.
  InCo-FIng-UDELAR
 */
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/usoTads.h"
#include "../include/iterador.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_avl
{
    TAvl left;
    TAvl right;
    nat dato;
    int altura;
    int cantidad;
};

TAvl crearAvl()
{
    TAvl avl = NULL;
    return avl;
}

bool estaVacioAvl(TAvl avl)
{
    return avl == NULL;
}

double max(double val1, double val2)
{
    if (val1 > val2)
        return val1;
    else
        return val2;
}
/*
void actualizarInfoAltura(TAvl n)
{
    double nActualAltura;
    if (n->left != NULL && n->right != NULL)
    {
        nActualAltura = maxAltura(realInfo(n->left->dato), realInfo(n->right->dato)) + 1;
    }
    else if (n->left != NULL)
    {
        nActualAltura = realInfo(n->left->dato) + 1;
    }
    else if (n->right != NULL)
    {
        nActualAltura = realInfo(n->right->dato) + 1;
    }
    else
    {
        nActualAltura = 0;
    }
    TInfo aux = n->dato;
    n->dato = crearInfo(natInfo(n->dato), nActualAltura);
    liberarInfo(aux);
}

TAvl rotacionSimpleAright(TAvl avl)
{
    TAvl n1 = avl;
    TAvl n2 = n1->left;
    n1->left = n2->right;
    n2->right = n1;
    avl = n2;
    actualizarInfoAltura(n1);
    actualizarInfoAltura(n2);
    return avl;
}

TAvl rotacionSimpleAleft(TAvl avl)
{
    TAvl n1 = avl;
    TAvl n2 = n1->right;
    n1->right = n2->left;
    n2->left = n1;
    avl = n2;
    actualizarInfoAltura(n1);
    actualizarInfoAltura(n2);
    return avl;
}

TAvl rotacionDobleAleft(TAvl avl)
{
    TAvl n1 = avl;
    n1->right = rotacionSimpleAright(n1->right);
    return rotacionSimpleAleft(n1);
}

TAvl rotacionDobleAright(TAvl avl)
{
    TAvl n1 = avl;
    n1->left = rotacionSimpleAleft(n1->left);
    return rotacionSimpleAright(n1);
}

int diferenciaDeAlturaleft(TAvl left, TAvl right)
{
    if (left == NULL && right == NULL)
    {
        return 0;
    }
    else if (left == NULL)
    {
        return -realInfo(right->dato);
    }
    else if (right == NULL)
    {
        return realInfo(left->dato);
    }
    else
        return (realInfo(left->dato) - realInfo(right->dato));
}

int diferenciaDeAlturaright(TAvl left, TAvl right)
{
    if (left == NULL && right == NULL)
    {
        return 0;
    }
    else if (left == NULL)
    {
        return realInfo(right->dato);
    }
    else if (right == NULL)
    {
        return -realInfo(left->dato);
    }
    else
        return realInfo(right->dato) - realInfo(left->dato);
}

TAvl balancear(TAvl &avl)
{
    if (diferenciaDeAlturaleft(avl->left, avl->right) == 2)
    {
        if (diferenciaDeAlturaleft(avl->left->left, avl->left->right) >= 0)
            avl = rotacionSimpleAright(avl);
        else
            avl = rotacionDobleAright(avl);
    }
    if (diferenciaDeAlturaright(avl->left, avl->right) == 2)
    {
        if (diferenciaDeAlturaright(avl->right->left, avl->right->right) >= 0)
            avl = rotacionSimpleAleft(avl);
        else
            avl = rotacionDobleAleft(avl);
    }
    actualizarInfoAltura(avl);
    return avl;
}


void insertarEnAvlAux(nat elem, TAvl &avl)
{
    if (avl == NULL)
    {
        avl = new _rep_avl;
        avl->dato = crearInfo(elem, 0);
        avl->left = NULL;
        avl->right = NULL;
    }
    else if (elem < natInfo(avl->dato))
    {
        insertarEnAvlAux(elem, avl->left);
        avl = balancear(avl);
    }
    else if (elem > natInfo(avl->dato))
    {
        insertarEnAvlAux(elem, avl->right);
        avl = balancear(avl);
    }
}

TAvl insertarEnAvl(nat elem, TAvl avl)
{
    insertarEnAvlAux(elem, avl);
    return avl;
}*/

void rotarADerecha(TAvl &z)
{ // precond : z y z->left != NULL
    TAvl y = z->left;
    TAvl T3 = y->right;
    y->right = z;
    z->left = T3;
    z->altura = max(alturaDeAvl(z->left), alturaDeAvl(z->right)) + 1;
    y->altura = max(alturaDeAvl(y->left), alturaDeAvl(y->right)) + 1;
    z->cantidad = cantidadEnAvl(z->left) + cantidadEnAvl(z->right) + 1;
    z = y;
}

void rotarAIzquierda(TAvl &z)
{ // precond : el z y z->right != Ã¢â€ Â- NULL
    TAvl y = z->right;
    TAvl T2 = y->left;
    y->left = z;
    z->right = T2;
    z->altura = max(alturaDeAvl(z->left), alturaDeAvl(z->right)) + 1;
    y->altura = max(alturaDeAvl(y->left), alturaDeAvl(y->right)) + 1;
    z->cantidad = cantidadEnAvl(z->left) + cantidadEnAvl(z->right) + 1;
    z = y;
}

void insertarEnAvlAux(nat elem, TAvl &avl)
{
    if (avl == NULL)
    { // caso base
        avl = new _rep_avl;
        avl->dato = elem;
        avl->left = avl->right = NULL;
        avl->altura = 1;
        avl->cantidad = 1;
    }
    else
    {
        if (elem < avl->dato)
        {
            insertarEnAvlAux(elem, avl->left);
            avl->altura = max(alturaDeAvl(avl->left), alturaDeAvl(avl->right)) + 1;
            // Factor de balanceo
            int FB = alturaDeAvl(avl->left) - alturaDeAvl(avl->right);
            if (FB > 1)
            {
                // sÃƒÂ³lo puede aumentar la altura del sub ÃƒÂ¡ rbol leftuiero
                if (alturaDeAvl(avl->left->left) > alturaDeAvl(avl->left->right))
                    // sub ÃƒÂ¡ rbol leftuierdo del subÃƒÂ¡ rbol leftuierdo muy alto
                    // caso LL o II
                    rotarADerecha(avl);
                else
                { // alturaDeAvl (A->left ->left)< alturaDeAvl (A->left->rightÃ¢â€ Â-)
                    // sub ÃƒÂ¡ rbol rightecho del subÃƒÂ¡ rbol leftuierdo muy alto
                    // caso LR o ID
                    rotarAIzquierda(avl->left);
                    rotarADerecha(avl);
                }
            }
            avl->cantidad = cantidadEnAvl(avl->left) + cantidadEnAvl(avl->right) + 1;
        }
        else if (elem > avl->dato)
        { // (x >=A-> dato )
            insertarEnAvlAux(elem, avl->right);
            avl->altura = max(alturaDeAvl(avl->left), alturaDeAvl(avl->right)) + 1;
            // Factor de balanceo
            int FB = alturaDeAvl(avl->left) - alturaDeAvl(avl->right);
            if (FB < -1)
            {
                // sÃƒÂ³lo puede aumentar la altura del sub ÃƒÂ¡ rbol rightecho
                if (alturaDeAvl(avl->right->right) > alturaDeAvl(avl->right->left))
                    // sub ÃƒÂ¡ rbol rightecho del subÃƒÂ¡ rbol rightecho muy alto
                    // caso RR o DD
                    rotarAIzquierda(avl);
                else
                { // ( alturaDeAvl (A->right ->right) < alturaDeAvl (A->right ->leftÃ¢â€ Â-))
                    // sub ÃƒÂ¡ rbol leftuierdo del subÃƒÂ¡ rbol rightecho muy alto
                    // caso RL o DI
                    rotarADerecha(avl->right);
                    rotarAIzquierda(avl);
                }
            }
            avl->cantidad = cantidadEnAvl(avl->left) + cantidadEnAvl(avl->right) + 1;
        }
    }
}

TAvl insertarEnAvl(nat elem, TAvl avl)
{
    insertarEnAvlAux(elem, avl);
    return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl)
{
    if (avl != NULL)
    {
        while (avl != NULL && avl->dato != elem)
        {
            if (avl->dato > elem)
                avl = avl->left;
            else
                avl = avl->right;
        }
    }
    return avl;
}

nat raizAvl(TAvl avl)
{
    assert(!estaVacioAvl(avl));
    return avl->dato;
}

TAvl izqAvl(TAvl avl)
{
    assert(!estaVacioAvl(avl));
    return avl->left;
}

TAvl derAvl(TAvl avl)
{
    assert(!estaVacioAvl(avl));
    return avl->right;
}

nat cantidadEnAvl(TAvl avl)
{
    if (avl != NULL)
        return avl->cantidad;
    else
        return 0;
}

nat alturaDeAvl(TAvl avl)
{
    if (avl != NULL)
        return avl->altura;
    else
        return 0;
}

TIterador enOrdenAvlAux(TIterador iter, TAvl a)
{
    if (a != NULL)
    {
        enOrdenAvlAux(iter, a->left);
        agregarAIterador(a->dato, iter);
        enOrdenAvlAux(iter, a->right);
    }
    return iter;
}

TIterador enOrdenAvl(TAvl avl)
{
    TIterador iteradorAvl = crearIterador();
    if (avl != NULL)
    {
        iteradorAvl = enOrdenAvlAux(iteradorAvl, avl);
    }
    return iteradorAvl;
}

void insertarEnAvlMinAux(nat elem, TAvl &avl)
{
    if (avl == NULL)
    { // caso base
        avl = new _rep_avl;
        avl->dato = elem;
        avl->left = avl->right = NULL;
        avl->altura = 1;
        avl->cantidad = 1;
    }
    else
    {
        if (elem < avl->dato)
        {
            insertarEnAvlAux(elem, avl->left);
            avl->altura = max(alturaDeAvl(avl->left), alturaDeAvl(avl->right)) + 1;
            // Factor de balanceo
            int FB = alturaDeAvl(avl->left) - alturaDeAvl(avl->right);
            if (FB > 1)
            {
                // sÃƒÂ³lo puede aumentar la altura del sub ÃƒÂ¡ rbol leftuiero
                if (alturaDeAvl(avl->left->left) > alturaDeAvl(avl->left->right))
                    // sub ÃƒÂ¡ rbol leftuierdo del subÃƒÂ¡ rbol leftuierdo muy alto
                    // caso LL o II
                    rotarADerecha(avl);
                else
                { // alturaDeAvl (A->left ->left)< alturaDeAvl (A->left->rightÃ¢â€ Â-)
                    // sub ÃƒÂ¡ rbol rightecho del subÃƒÂ¡ rbol leftuierdo muy alto
                    // caso LR o ID
                    rotarAIzquierda(avl->left);
                    rotarADerecha(avl);
                }
            }
            avl->cantidad = cantidadEnAvl(avl->left) + cantidadEnAvl(avl->right) + 1;
        }
        else if (elem > avl->dato)
        { // (x >=A-> dato )
            insertarEnAvlAux(elem, avl->right);
            avl->altura = max(alturaDeAvl(avl->left), alturaDeAvl(avl->right)) + 1;
            // Factor de balanceo
            int FB = alturaDeAvl(avl->left) - alturaDeAvl(avl->right);
            if (FB < -1)
            {
                // sÃƒÂ³lo puede aumentar la altura del sub ÃƒÂ¡ rbol rightecho
                if (alturaDeAvl(avl->right->right) > alturaDeAvl(avl->right->left))
                    // sub ÃƒÂ¡ rbol rightecho del subÃƒÂ¡ rbol rightecho muy alto
                    // caso RR o DD
                    rotarAIzquierda(avl);
                else
                { // ( alturaDeAvl (A->right ->right) < alturaDeAvl (A->right ->leftÃ¢â€ Â-))
                    // sub ÃƒÂ¡ rbol leftuierdo del subÃƒÂ¡ rbol rightecho muy alto
                    // caso RL o DI
                    rotarADerecha(avl->right);
                    rotarAIzquierda(avl);
                }
            }
            avl->cantidad = cantidadEnAvl(avl->left) + cantidadEnAvl(avl->right) + 1;
        }
    }
}

TAvl insertarEnAvlMin(nat elem, TAvl avl)
{
    insertarEnAvlAux(elem, avl);
    return avl;
}

TAvl arregloAAvlAux(ArregloNats elems, int inicio, int final, TAvl avl)
{
    if (inicio > final)
        return NULL;
    else
    {
        int pos = (final + inicio) / 2;
        avl = new _rep_avl;
        avl->dato = elems[pos];
        avl->left = arregloAAvlAux(elems, inicio, pos - 1, avl);
        avl->right = arregloAAvlAux(elems, pos + 1, final, avl);
        avl->cantidad = cantidadEnAvl(avl->left) + cantidadEnAvl(avl->right) + 1;
        avl->altura = max(alturaDeAvl(avl->left), alturaDeAvl(avl->right)) + 1;
        return avl;
    }
}

TAvl arregloAAvl(ArregloNats elems, nat n)
{
    TAvl avl = crearAvl();
    if (n > 0){
        avl = arregloAAvlAux(elems, 0, n-1, avl);
    }
    return avl;
}

TAvl avlMinAux(nat h, TAvl avl, nat &min)
{
    if (h != 0)
    {
        if (h == 1)
        {
            avl = insertarEnAvl(min, avl);
            min++;
        }
        else
        {
            avl = insertarEnAvl(min, avl);
            avl->left = avlMinAux(h - 1, avl->left, min);
            avl->dato = min;
            min++;
            avl->right = avlMinAux(h - 2, avl->right, min);
        }
    }
    return avl;
}

TAvl avlMin(nat h)
{
    TAvl avl = crearAvl();
    nat min = 1;
    return avlMinAux(h, avl, min);
}

void liberarAvl(TAvl avl)
{
    if (avl != NULL)
    {
        liberarAvl(avl->left);
        liberarAvl(avl->right);
        delete avl;
    }
    else
        delete avl;
}