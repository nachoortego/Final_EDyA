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
  char* direccion = malloc(sizeof(char) * capacidad);
  arr->capacidad = capacidad;
  arr->direccion = direccion;
  arr->ultimo = 0;
  return arr;
}

/**
 * Libera la memoria utilizada por el arreglo.
 *
 * @param arr Puntero al arreglo a destruir.
 */
void arreglo_destruir(Arreglo arr) {
  free(arr->direccion);
  free(arr);
}

/**
 * Escribe un dato en el arreglo. Si el arreglo está lleno, duplica su capacidad.
 *
 * @param arr Puntero al arreglo.
 * @param dato Caracter a añadir al arreglo.
 */
void arreglo_escribir(Arreglo arr, char dato) {
  arr->direccion[arr->ultimo] = dato;
  arr->ultimo++;
  if (arr->ultimo == arr->capacidad) {
    arr->capacidad *= 2;
    arr->direccion = realloc(arr->direccion, sizeof(char) * arr->capacidad);
  }
}

/**
 * Obtiene la capacidad actual del arreglo.
 *
 * @param arreglo Puntero al arreglo.
 * @return Capacidad del arreglo.
 */
int arreglo_capacidad(Arreglo arreglo) {
  return arreglo->capacidad;
}

/**
 * Imprime el contenido del arreglo.
 *
 * @param arreglo Puntero al arreglo.
 */
void arreglo_imprimir(Arreglo arreglo) {
  for (int i = 0; i < arreglo->ultimo; i++)
    printf("%c", arreglo->direccion[i]);
  printf("\n");
}
