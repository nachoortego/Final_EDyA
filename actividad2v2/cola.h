#ifndef COLA_PRIORIDAD_H
#define COLA_PRIORIDAD_H

#include "punto.h"

// Estructura para representar una cola de prioridad utilizando un heap binario
typedef struct {
  Punto* data;
  int size;
  int capacity;
} _ColaP;

typedef _ColaP* ColaP;

// Función para crear una cola de prioridad con una capacidad inicial
ColaP cola_crear(int capacity);

// Función para insertar un nuevo elemento en la cola de prioridad
void cola_insertar(ColaP cp, Punto p);

// Función para extraer el elemento de mayor prioridad (mínimo) de la cola
Punto cola_extraer_min(ColaP cp);

// Función para verificar si la cola de prioridad está vacía
int cola_vacia(ColaP cp);

// Función para destruir la cola de prioridad y liberar la memoria
void cola_destruir(ColaP cp);

#endif // COLA_PRIORIDAD_H
