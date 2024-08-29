#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cola.h"

Cola cola_crear(int capacity) {
  Cola cp = (Cola)malloc(sizeof(_Cola));
  assert(cp != NULL);

  cp->data = (Punto*)malloc(capacity * sizeof(Punto));
  assert(cp->data != NULL);

  cp->size = 0;
  cp->capacity = capacity;
  return cp;
}

void cola_insertar(Cola cp, Punto p) {
  if (cp->size >= cp->capacity) {
    // Si la cola está llena, aumentamos su capacidad
    cp->capacity *= 2;
    cp->data = (Punto*)realloc(cp->data, cp->capacity * sizeof(Punto));
    assert(cp->data != NULL);
  }
  cp->data[cp->size++] = p; // Insertar el elemento al final
}

Punto cola_extraer(Cola cp) {
  assert(cp->size > 0); // Asegurarse de que la cola no está vacía

  Punto primero = cp->data[0];

  // Desplazar todos los elementos hacia la izquierda
  for (int i = 1; i < cp->size; i++) {
    cp->data[i - 1] = cp->data[i];
  }

  cp->size--; // Reducir el tamaño de la cola
  return primero;
}

int cola_vacia(Cola cp) {
  return cp->size == 0;
}

void cola_destruir(Cola cp) {
  if (cp) {
    free(cp->data);
    free(cp);
  }
}
