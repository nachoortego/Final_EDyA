#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "punto.h"

// Función para intercambiar dos elementos en el heap
static void swap(Punto* a, Punto* b) {
  Punto temp = *a;
  *a = *b;
  *b = temp;
}

// Función para mantener la propiedad de heap al subir un elemento
static void heapifyUp(ColaP cp, int index) {
  int parent = (index - 1) / 2;

  if (index > 0 && cp->data[index].costo < cp->data[parent].costo) {
    swap(&cp->data[index], &cp->data[parent]);
    heapifyUp(cp, parent);
  }
}

// Función para mantener la propiedad de heap al bajar un elemento
static void heapifyDown(ColaP cp, int index) {
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;
  int smallest = index;

  if (leftChild < cp->size && cp->data[leftChild].costo < cp->data[smallest].costo) {
    smallest = leftChild;
  }

  if (rightChild < cp->size && cp->data[rightChild].costo < cp->data[smallest].costo) {
    smallest = rightChild;
  }

  if (smallest != index) {
    swap(&cp->data[index], &cp->data[smallest]);
    heapifyDown(cp, smallest);
  }
}

// Función para inicializar la cola de prioridad
ColaP cola_crear(int capacity) {
  ColaP cp = (ColaP)malloc(sizeof(_ColaP));
  cp->data = (Punto*)malloc(capacity * sizeof(Punto));
  cp->size = 0;
  cp->capacity = capacity;
  return cp;
}

// Función para insertar un nuevo elemento en la cola de prioridad
void cola_insertar(ColaP cp, Punto p) {
  if (cp->size == cp->capacity) {
    cp->capacity *= 2;
    cp->data = (Punto*)realloc(cp->data, cp->capacity * sizeof(Punto));
  }

  cp->data[cp->size] = p;
  heapifyUp(cp, cp->size);
  cp->size++;
}

// Función para extraer el elemento de mayor prioridad (mínimo)
Punto cola_extraer_min(ColaP cp) {
  if (cp->size == 0) {
    fprintf(stderr,"Error: la cola de prioridad está vacía.\n");
    exit(EXIT_FAILURE);
  }

  Punto min = cp->data[0];
  cp->data[0] = cp->data[cp->size - 1];
  cp->size--;
  heapifyDown(cp, 0);

  return min;
}

// Función para liberar la memoria de la cola de prioridad
void cola_destruir(ColaP cp) {
  free(cp->data);
  free(cp);
}

// Función para verificar si la cola está vacía
int cola_vacia(ColaP cp) {
  return cp->size == 0;
}
