#ifndef COLA_H
#define COLA_H

#include "punto.h"

// Estructura para representar una cola
typedef struct {
  Punto* data;
  int size;
  int capacity;
} _Cola;

typedef _Cola* Cola;

// Función para crear una cola con una capacidad inicial
Cola cola_crear(int capacity);

// Función para insertar un nuevo elemento en la cola
void cola_insertar(Cola cp, Punto p);

// Función para extraer el elemento de mayor antiguedad de la cola
Punto cola_extraer(Cola cp);

// Función para verificar si la cola está vacía
int cola_vacia(Cola cp);

// Función para destruir la cola y liberar la memoria
void cola_destruir(Cola cp);

#endif // COLA_H
