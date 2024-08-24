#ifndef ARREGLO_H
#define ARREGLO_H

#include <stdlib.h>

typedef void (*FuncionVisitante)(void *dato);
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);

typedef struct {
  void** direccion;
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
 * @param dest Función que libera la memoria de un elemento del arreglo.
 */
void arreglo_destruir(Arreglo arr, FuncionDestructora dest);

/**
 * Escribe un dato en el arreglo. Si el arreglo está lleno, duplica su capacidad.
 *
 * @param arr Puntero al arreglo.
 * @param dato Dato a añadir al arreglo.
 * @param copy Función que copia un elemento del arreglo.
 */
void arreglo_escribir(Arreglo arr, void* dato, FuncionCopia copy);

/**
 * Obtiene la capacidad actual del arreglo.
 *
 * @param arr Puntero al arreglo.
 * @return Capacidad del arreglo.
 */
int arreglo_capacidad(Arreglo arr);

/**
 * Imprime el contenido del arreglo.
 *
 * @param arr Puntero al arreglo.
 * @param visit Función que imprime un elemento del arreglo.
 */
void arreglo_recorrer(Arreglo arr, FuncionVisitante visit);

#endif // ARREGLO_H
