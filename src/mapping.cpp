#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/usoTads.h"
#include "../include/iterador.h"
#include "../include/colaDePrioridad.h"
#include "../include/mapping.h"
#include "../include/cadena.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_mapping
{
  TCadena *array;
  nat contador;
  nat tamanio;
};

bool esPrimo(int numero)
{
  // Casos especiales
  if (numero == 0 || numero == 1 || numero == 4)
    return false;
  for (int x = 2; x < numero / 2; x++)
  {
    if (numero % x == 0)
      return false;
  }
  // Si no se pudo dividir por ninguno de los de arriba, sí es primo
  return true;
}

/*
  Crea un 'TMapping' vacío (sin elementos) de asociaciones nat -> double.
  Podrá haber hasta M asociaciones.
  El tiempo de ejecución en el peor caso es O(M).
 */

void crearMapAux(nat M, TMapping &map){
  if (esPrimo(M))
  {
    map = new _rep_mapping;
    map->array = new TCadena[M];
    nat i = 0;
    while (i < M)
    {
      map->array[i] = crearCadena();
      i++;
    }
    map->contador = 0;
    map->tamanio = M;
  }
  else
    crearMapAux(M + 1, map);
}

TMapping crearMap(nat M)
{
  TMapping map;
  crearMapAux(M, map);
  return map;
}

nat posDeHash(nat clave, TMapping map)
{
  return clave % map->tamanio;
}
/*
  Inserta en 'map' la asociación entre 'clave' y 'valor'.
  Precondición: !estaLlenoMap(map) y !existeAsociacionEnMap(clave, map).
  Devuelve 'map'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TMapping asociarEnMap(nat clave, double valor, TMapping map)
{
  if (inicioCadena(map->array[posDeHash(clave, map)]) == NULL)
    insertarAlFinal(crearInfo(clave, valor), map->array[posDeHash(clave, map)]);
  else
    insertarAntes(crearInfo(clave, valor), inicioCadena(map->array[posDeHash(clave, map)]), map->array[posDeHash(clave, map)]);
  map->contador++;
  return map;
}

/*
  Elimina de 'map' la asociación correspondiente a 'clave' y libera la
  memoria  asignada a mantener esa asociación.
  Precondición: existeAsociacionenMap(clave, h).
  Devuelve 'map'.
  El 'TMapping' resultado comparte memoria con el parámetro'.
  El tiempo de ejecución es O(1) en promedio.
 */
TMapping desasociarEnMap(nat clave, TMapping map)
{
  nat i = posDeHash(clave, map);
  TLocalizador loc = inicioCadena(map->array[i]);
  while (esLocalizador(loc) && natInfo(infoCadena(loc, map->array[i])) != clave)
  {
    loc = siguiente(loc, map->array[i]);
  }
  removerDeCadena(loc, map->array[i]);
  return map;
}

/*
  Devuelve 'true' si y solo si en 'map' hay una asociación correspondiente
  a 'clave'.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existeAsociacionEnMap(nat clave, TMapping map)
{
  nat i = posDeHash(clave, map);
  return pertenece(clave, map->array[i]);
}

/*
  Devuelve el valor correspondiente a la asociacion de 'clave' en 'h'.
  Precondición: existeAsociacionenMap(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
double valorEnMap(nat clave, TMapping map)
{
  nat i = posDeHash(clave, map);
  TLocalizador loc = inicioCadena(map->array[i]);
  while (esLocalizador(loc) && natInfo(infoCadena(loc, map->array[i])) != clave)
  {
    loc = siguiente(loc, map->array[i]);
  }
  return realInfo(infoCadena(loc, map->array[i]));
}

/*
  Devuelve 'true' si y solo si 'map' tiene 'M' elementos, siendo 'M' el
  parámetro pasado en crearMap.
  El tiempo de ejecución es O(1).
 */
bool estaLlenoMap(TMapping map){
  return map->contador == map->tamanio;
}

/*
  Libera la memoria asignada a 'map' y todos sus elementos.
  El tiempo de ejecución en el peor caso es O(M), siendo 'M' el parámetro
  pasado en crearMap.
 */
void liberarMap(TMapping map){
  nat i = 0;
  if (map != NULL){
    while(i < map->tamanio){
    liberarCadena(map->array[i]);
    i++;
    }
    delete [] map->array;
  delete map;
  }
}