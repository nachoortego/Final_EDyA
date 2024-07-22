#include "array.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Crea un nuevo arreglo con una capacidad inicial.
 *
 * @param capacidad Capacidad inicial del arreglo.
 * @return Un puntero a la estructura del arreglo.
 */
Arreglo arreglo_crear(int capacidad) {
  Arreglo arr = malloc(sizeof(_Arreglo));
  void** direccion = malloc(sizeof(void*) * capacidad);
  arr->capacidad = capacidad;
  arr->direccion = direccion;
  arr->ultimo = 0;
  return arr;
}

/**
 * Libera la memoria utilizada por el arreglo.
 *
 * @param arr Puntero al arreglo a destruir.
 * @param dest Función que libera la memoria de un elemento del arreglo.
 */
void arreglo_destruir(Arreglo arr, FuncionDestructora dest) {
  for (int i = 0; i < arr->ultimo; i++)
    dest(arr->direccion[i]);
  free(arr->direccion);
  free(arr);
}

/**
 * Escribe un dato en el arreglo. Si el arreglo está lleno, duplica su capacidad.
 *
 * @param arr Puntero al arreglo.
 * @param dato Dato a añadir al arreglo.
 * @param copy Función que copia un elemento del arreglo.
 */
void arreglo_escribir(Arreglo arr, void* dato, FuncionCopia copy) {
  arr->direccion[arr->ultimo] = copy(dato);
  arr->ultimo++;
  if (arr->ultimo == arr->capacidad) {
    arr->capacidad *= 2;
    arr->direccion = realloc(arr->direccion, sizeof(void*) * arr->capacidad);
  }
}

/**
 * Obtiene la capacidad actual del arreglo.
 *
 * @param arr Puntero al arreglo.
 * @return Capacidad del arreglo.
 */
int arreglo_capacidad(Arreglo arr) {
  return arr->capacidad;
}

/**
 * Imprime el contenido del arreglo.
 *
 * @param arreglo Puntero al arreglo.
 * @param visit Función que imprime un elemento del arreglo.
 */
void arreglo_recorrer(Arreglo arr, FuncionVisitante visit) {
  for (int i = 0; i < arr->ultimo; i++)
    visit(arr->direccion[i]);
}
