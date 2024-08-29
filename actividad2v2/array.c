#include "array.h"
#include <stdio.h>
#include <stdlib.h>

Arreglo arreglo_crear(int capacidad) {
  Arreglo arr = malloc(sizeof(_Arreglo));
  void** direccion = malloc(sizeof(void*) * capacidad);
  arr->capacidad = capacidad;
  arr->direccion = direccion;
  arr->ultimo = 0;
  return arr;
}

void arreglo_destruir(Arreglo arr, FuncionDestructora dest) {
  for (int i = 0; i < arr->ultimo; i++)
    dest(arr->direccion[i]);
  free(arr->direccion);
  free(arr);
}

void arreglo_escribir(Arreglo arr, void* dato, FuncionCopia copy) {
  arr->direccion[arr->ultimo] = copy(dato);
  arr->ultimo++;
  if (arr->ultimo == arr->capacidad) {
    arr->capacidad *= 2;
    arr->direccion = realloc(arr->direccion, sizeof(void*) * arr->capacidad);
  }
}

int arreglo_capacidad(Arreglo arr) {
  return arr->capacidad;
}

void arreglo_recorrer(Arreglo arr, FuncionVisitante visit) {
  for (int i = 0; i < arr->ultimo; i++)
    visit(arr->direccion[i]);
}
