#ifndef ARREGLO_H
#define ARREGLO_H

#include <stdlib.h>

typedef struct {
  char* direccion;
  int ultimo;
  size_t capacidad;
} _Arreglo;

typedef _Arreglo* Arreglo;

/**
 * Crea un nuevo arreglo con una capacidad inicial.
 *
 * @param capacidad Capacidad inicial del arreglo.
 * @return Un puntero a la estructura del arreglo.
 */
Arreglo arreglo_crear(int capacidad);

/**
 * Libera la memoria utilizada por el arreglo.
 *
 * @param arr Puntero al arreglo a destruir.
 */
void arreglo_destruir(Arreglo arr);

/**
 * Escribe un dato en el arreglo. Si el arreglo está lleno, duplica su capacidad.
 *
 * @param arr Puntero al arreglo.
 * @param dato Caracter a añadir al arreglo.
 */
void arreglo_escribir(Arreglo arr, char dato);

/**
 * Obtiene la capacidad actual del arreglo.
 *
 * @param arreglo Puntero al arreglo.
 * @return Capacidad del arreglo.
 */
int arreglo_capacidad(Arreglo arreglo);

/**
 * Imprime el contenido del arreglo.
 *
 * @param arreglo Puntero al arreglo.
 */
void arreglo_imprimir(Arreglo arreglo);

#endif // ARREGLO_H
