#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/usoTads.h"
#include "../include/iterador.h"
#include "../include/colaDePrioridad.h"
#include "../include/cadena.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_colaDePrioridad {
  TInfo *heap;
  nat *posiciones;
  nat tope;
  nat valorMax;
};

/*
  Devuelve una 'TColaDePrioridad' vacía (sin elementos). Podrá contener
  elementos entre 1 y N.
  El tiempo de ejecución en el peor caso es O(N).
 */
TColaDePrioridad crearCP(nat N){
  TColaDePrioridad cp = new _rep_colaDePrioridad;
  cp->heap = new TInfo[N+1];
  for (nat i = 0; i <= N; i++){
    cp->heap[i] = NULL;
  }
  cp->posiciones = new nat[N+1];
  for (nat i = 0; i <= N; i++){
    cp->posiciones[i] = 0;
  }
  cp->tope = 0;
  cp->valorMax = N;
  return cp;
}

/*
  Devuelve el valor máximo que puede tener un elemento de 'cp', que es el
  parámetro de crearCP.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat rangoCP(TColaDePrioridad cp){
  return cp->valorMax;
}

void filtradoAscendente(uint pos, TColaDePrioridad cp) {
  /*for (nat i = 1; i <= cp->tope; i++)
  {
    printf("%i", natInfo(cp->heap[i]));
    printf("%f", realInfo(cp->heap[i]));
    printf("%s", "|");
  }
  printf("\n");
  printf("\n");
  printf("\n");
  printf("%s\n", "posiciones");
  for (nat i = 0; i <= cp->valorMax; i++)
  {
    printf("%i", cp->posiciones[i]);
  }
  printf("\n");*/
  if (pos > 1 && realInfo(cp->heap[pos]) < realInfo(cp->heap[pos/2])) {
    TInfo auxHijo = cp->heap[pos];
    cp->heap[pos] = cp->heap[pos/2];
    cp->heap[pos/2] = auxHijo;
    cp->posiciones[natInfo(cp->heap[pos/2])] = pos/2;
    cp->posiciones[natInfo(cp->heap[pos])] = pos;
    filtradoAscendente(pos/2, cp);
  }
}

/*
  Inserta 'elem' en 'cp'. La prioridad asociada a 'elem' es 'valor'.
  Precondición 1 <= elem <= rangoCP(cp).
  Precondición: !estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){

  if (elem <= cp->valorMax && cp->tope <= cp->valorMax) {
    cp->tope = cp->tope + 1;
    cp->heap[cp->tope] = crearInfo(elem, valor);
    cp->posiciones[elem] = cp->tope;
    filtradoAscendente(cp->tope, cp);
  }
  return cp;
}

/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor casos es O(1).
 */
bool estaVaciaCP(TColaDePrioridad cp){
  return cp->heap[1] == NULL;
}

/*
  Devuelve el elemento prioritario de 'cp'.
  Precondición: !estaVacioCP(cp).
  El tiempo de ejecución en el peor casos es O(1).
 */
nat prioritario(TColaDePrioridad cp){
  return natInfo(cp->heap[1]);
}

void filtradoDescendente(nat &pos, TColaDePrioridad cp) {
  /*for (nat i = 1; i <= cp->tope; i++)
  {
    printf("%i", natInfo(cp->heap[i]));
    printf("%f", realInfo(cp->heap[i]));
    printf("%s", "|");
  }
  printf("\n");
  printf("\n");
  printf("\n");
  printf("%s\n", "posiciones");
  for (nat i = 0; i <= cp->valorMax; i++)
  {
    printf("%i", cp->posiciones[i]);
  }
  printf("\n");*/
  nat posHijo = 2 * pos;
  if (posHijo <= cp->tope) {
    if ((2*pos)+1 <= cp->tope && realInfo(cp->heap[(2*pos)+1]) <= realInfo(cp->heap[posHijo])) {
      posHijo = (2*pos) + 1;
    }
    if (realInfo(cp->heap[posHijo]) < realInfo(cp->heap[pos])) {
      TInfo auxPadre = cp->heap[pos];
      cp->heap[pos] = cp->heap[posHijo];
      cp->heap[posHijo] = auxPadre;
      cp->posiciones[natInfo(cp->heap[posHijo])] = posHijo;
      cp->posiciones[natInfo(cp->heap[pos])] = pos;
      filtradoDescendente(posHijo, cp);
    }
  }
}

/*resp
void filtradoDescendente(nat pos, TColaDePrioridad cp){
  nat posHijo = 2 * cp->posiciones[natInfo(cp->heap[1])];
  if (posHijo <= cp->tope && cp->heap[cp->posiciones[posHijo + 1]] < cp->heap[cp->posiciones[posHijo]]) {
    posHijo = posHijo + 1;
  }
  if (realInfo(cp->heap[cp->posiciones[posHijo]]) < realInfo(cp->heap[cp->posiciones[pos]])) {
    TInfo auxPadre = cp->heap[cp->posiciones[pos]];
    cp->heap[cp->posiciones[pos]] = cp->heap[cp->posiciones[posHijo]];
    cp->heap[cp->posiciones[posHijo]] = auxPadre;
    cp->posiciones[pos] = cp->posiciones[posHijo];
    cp->posiciones[posHijo] = pos;
    filtradoDescendente(posHijo, cp);
  }
}*/

/*void filtradoDescendente(nat pos, TColaDePrioridad &cp){
  TInfo auxPadre = cp->heap[pos];
  if (2*pos <= cp->tope){
    while (2*pos <= cp->tope && realInfo(auxPadre) > realInfo(cp->heap[pos*2])) {
      nat posHijo = cp->posiciones[natInfo(cp->heap[2*pos])];
      if (((2*pos)+1) <= cp->tope && realInfo(cp->heap[(2*pos)+1]) < realInfo(cp->heap[2*pos])) {
        posHijo = cp->posiciones[natInfo(cp->heap[(2*pos)+1])];
      }
      if (realInfo(auxPadre) > realInfo(cp->heap[posHijo])) {
        cp->heap[pos] = cp->heap[posHijo];
        cp->posiciones[natInfo(cp->heap[posHijo])] = pos;
        cp->posiciones[natInfo(cp->heap[pos])] = posHijo; //
        pos = posHijo;
      }
      cp->heap[pos] = auxPadre;
      cp->posiciones[natInfo(auxPadre)] = pos;
    }
  }
}*/

/*void filtradoDescendente(nat pos, TColaDePrioridad &cp){
  TInfo auxPadre = cp->heap[pos];
  if (2*pos <= cp->tope) {
    do {
      nat posHijo = cp->posiciones[natInfo(cp->heap[2*pos])];
      if (((2*pos)+1) <= cp->tope && realInfo(cp->heap[(2*pos)+1]) < realInfo(cp->heap[2*pos])) {
        posHijo = cp->posiciones[natInfo(cp->heap[(2*pos)+1])];
      }
      if (realInfo(auxPadre) > realInfo(cp->heap[posHijo])) {
        cp->heap[pos] = cp->heap[posHijo];
        cp->posiciones[natInfo(cp->heap[posHijo])] = pos;
        cp->posiciones[natInfo(cp->heap[pos])] = posHijo; //
        pos = posHijo;
      } 
    } while (2*pos <= cp->tope && realInfo(auxPadre) > realInfo(cp->heap[pos*2]));
    cp->heap[pos] = auxPadre;
    cp->posiciones[natInfo(auxPadre)] = pos;
  } 
}*/

/*
  Elimina de 'cp' el elemento prioritario.
  Precondición: !estaVacioCP(cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
  if (cp->tope > 1) {
    cp->posiciones[natInfo(cp->heap[1])] = 0;
    liberarInfo(cp->heap[1]);
    cp->heap[1] = cp->heap[cp->tope];
    cp->posiciones[natInfo(cp->heap[cp->tope])] = 1;
    cp->heap[cp->tope] = NULL;
    cp->tope--;
    if (cp->tope > 1) {
      nat posuno = 1;
      filtradoDescendente(posuno, cp);
    }
  } else if (cp->tope == 1) {
    cp->posiciones[natInfo(cp->heap[1])] = 0;
    liberarInfo(cp->heap[1]);
    cp->heap[1] = NULL;
    cp->tope--;
  }
  return cp;
}

/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat elem, TColaDePrioridad cp){
  if (elem > 0 && elem <= cp->valorMax)
    return cp->posiciones[elem] != 0 && cp->posiciones[elem] <= cp->tope;
  else 
    return false;
}

/*
  Devuelve el valor de prioridad asociado a 'elem'.
  Precondición: estaEnCp(elem, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */
double prioridad(nat elem, TColaDePrioridad cp){
  return realInfo(cp->heap[cp->posiciones[elem]]);
}

/*
  Modifica el valor de la propiedad asociada a 'elem'; pasa a ser 'valor'.
  Precondición: estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  nat pos = cp->posiciones[elem];
  double ordenAnt = realInfo(cp->heap[pos]);
  liberarInfo(cp->heap[cp->posiciones[elem]]);
  cp->heap[pos] = crearInfo(elem, valor);
  if (ordenAnt > valor)
    filtradoAscendente(pos, cp);
  else {
    filtradoDescendente(pos, cp);
  }
  return cp;
}

/*
  Libera la menoria asignada a 'cp'.
  El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
  pasado en crearCP.
 */
void liberarCP(TColaDePrioridad cp){
  //
  for (nat i = 0; i <= 10; i++){
    if (cp->heap[i] != NULL) 
    {
      liberarInfo(cp->heap[i]);
    }     
  }
  delete [] cp->heap;
  delete [] cp->posiciones;
  delete cp;
}