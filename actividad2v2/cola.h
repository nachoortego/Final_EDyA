#ifndef COLA_H
#define COLA_H

#include "punto.h"

// Estructura para representar una cola
typedef struct {
  Punto* data;
  int size;
  int capacity;
} _ColaP;

typedef _ColaP* ColaP;

// Función para crear una cola con una capacidad inicial
ColaP cola_crear(int capacity);

// Función para insertar un nuevo elemento en la cola
void cola_insertar(ColaP cp, Punto p);

// Función para extraer el elemento de mayor antiguedad de la cola
Punto cola_extraer(ColaP cp);

// Función para verificar si la cola está vacía
int cola_vacia(ColaP cp);

// Función para destruir la cola y liberar la memoria
void cola_destruir(ColaP cp);

#endif // COLA_H
