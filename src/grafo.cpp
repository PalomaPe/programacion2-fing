#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/usoTads.h"
#include "../include/iterador.h"
#include "../include/colaDePrioridad.h"
#include "../include/grafo.h"
#include "../include/mapping.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_grafo {
    TMapping map;
    TAvl *array;
    nat cantidadVertices;
    nat cantidadParejasVecinos;
    nat topeParejasVecinos;
};

/*
  Devuelve un 'TGrafo' con 'N' vértices identificados desde 1 hasta 'N'
  sin parejas de vecinos establecidos.
  Podŕa haber hasta 'M' parejas de vecinos.
  El tiempo de ejecución en peor caso es O(max{N,M}).
 */
TGrafo crearGrafo(nat N, nat M){
  TGrafo grafo = new _rep_grafo;
  grafo->map = crearMap(N);
  grafo->array = new TAvl[N];
  nat i = 0;
  while (i < N) {
    grafo->array[i] = crearAvl();
    i++;
  }
  grafo->cantidadVertices = N;
  grafo->cantidadParejasVecinos = 0;
  grafo->topeParejasVecinos = M;
  return grafo;
}

/*
  Devuelve la cantidad de vértices de 'g'.
  El tiempo de ejecución en peor caso es O(1).
 */
nat cantidadVertices(TGrafo g){
  return g->cantidadVertices;
}

/*
  Devuelve 'true' si y solo si en 'g' ya hay M parejas de vecinos,
  siendo M el segundo parámetro pasado en crearGrafo.
  El tiempo de ejecución en peor caso es O(1).
 */
bool hayMParejas(TGrafo g){
  return g->cantidadParejasVecinos == g->topeParejasVecinos;
}

nat posDeHash(nat clave, nat cantidadVertices)
{
  return clave % cantidadVertices;
}

/*
  Establece que 'v1' y 'v2' son vecinos en 'g' y la distancia entre ambos es
  'd'.
  Precondición: 1 <= v1, v2 <= N.
  Precondición: v1 != v2
  Precondición: !sonVecinos(v1, v2, g).
  Precondición: !hayMParejas(g).
  Precondición: d >= 0.
  Devuelve 'g'.
  El tiempo de ejecución es en peor caso O(max{log n1, log n2}), siendo 'n1' y
  'n2' la cantidad de vecinos de 'v1' y 'v2' respectivamente.
 */
TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
  if (g->cantidadParejasVecinos < g->topeParejasVecinos) {
    asociarEnMap(v1, d, g->map);
    asociarEnMap(v2, d, g->map);
    g->array[posDeHash(v1, g->cantidadVertices)] = insertarEnAvl(v2, g->array[posDeHash(v1, g->cantidadVertices)]);
    g->array[posDeHash(v2, g->cantidadVertices)] = insertarEnAvl(v1, g->array[posDeHash(v2, g->cantidadVertices)]);
    g->cantidadParejasVecinos++;
  }
  return g;
}

/*
  Devuelve 'true' si y solo si 'v1' y 'v2' son vecinos.
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
bool sonVecinos(nat v1, nat v2, TGrafo g){
  return !estaVacioAvl(buscarEnAvl(v1, g->array[posDeHash(v2, g->cantidadVertices)])) || !estaVacioAvl(buscarEnAvl(v2, g->array[posDeHash(v1, g->cantidadVertices)]));
}

nat max(nat v1, nat v2){
  if (v1 > v2){
    return v1;
  } else return v2;
}

nat min(nat v1, nat v2){
  if (v1 < v2){
    return v1;
  } else return v2;
}

/*
  Devuelve la distancia entre 'v1' y 'v2'.
  Precondición: sonVecinos(v1, v2, g).
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */

double valorAbsoluto(double a, double b) {
  if (a > b)
    return a-b;
  else return b-a;
}


double distancia(nat v1, nat v2, TGrafo g){
  return valorEnMap(v1, g->map);
}

/*
  Devuelve un 'TIterador' con los vecinos de 'v' ordenados de manera creciente.
  Precondición: 1 <= v <= N.
  El tiempo de ejecución en peor caso es O(n), siendo 'n' la cantidad de
  vecinos de 'v'.
 */
TIterador vecinos(nat v, TGrafo g){
  return enOrdenAvl(g->array[posDeHash(v, g->cantidadVertices)]);
}

/*
  Libera la memoria asignada a 'g'.
  El tiempo de ejecuión en el peor caso en O(N*N + M), siende 'N' y 'M' los
  parámetros pasados en crearGrafo.
 */
void liberarGrafo(TGrafo g){
  liberarMap(g->map);
  nat i = 0;
  while (i < g->cantidadVertices){
    liberarAvl(g->array[i]);
    i++;
  }
  delete [] g->array;
  delete g;
}
