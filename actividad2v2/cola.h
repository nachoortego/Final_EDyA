#ifndef COLA_H
#define COLA_H

#include "punto.h"

/**
 * Estructura para representar una cola que almacena elementos de tipo Punto.
 * 
 * @param data puntero a Punto para el dato.
 * @param capacity Número actual de elementos en la cola.
 * @param capacity Capacidad máxima del arreglo antes de redimensionar..
 */
typedef struct {
  Punto* data;
  int size;
  int capacity;
} _Cola;

typedef _Cola* Cola;

/**
 * Crea una cola con una capacidad dada.
 * 
 * @param capacity Capacidad inicial de la cola.
 * @return Un puntero a la nueva cola creada.
 */
Cola cola_crear(int capacity);

/**
 * Inserta un nuevo elemento en la cola.
 * 
 * @param cp Puntero a la cola donde se insertará el nuevo elemento.
 * @param p Punto que se va a insertar en la cola.
 */
void cola_insertar(Cola cp, Punto p);

/**
 * Extrae el elemento de mayor antigüedad de la cola.
 *
 * @param cp Puntero a la cola de la que se extraerá el elemento.
 * @return El Punto extraído de la cola. Si la cola está vacía, el comportamiento es indefinido.
 */
Punto cola_extraer(Cola cp);

/**
 * Verifica si la cola está vacía.
 *
 * @param cp Puntero a la cola que se va a verificar.
 * @return 1 si la cola está vacía, 0 en caso contrario.
 */
int cola_vacia(Cola cp);

/**
 * Destruye la cola y libera la memoria.
 *
 * @param cp Puntero a la cola que se va a destruir.
 */
void cola_destruir(Cola cp);

#endif // COLA_H
