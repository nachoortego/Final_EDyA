#include "punto.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * Función hash para la estructura Punto.
 * Retorna un valor hash para el punto (x, y).
 */
unsigned hash_punto(void* punto) {
  Punto* p = (Punto*)punto;
  return (unsigned)(p->x * 31 + p->y);
}

/**
 * Función de comparación para la estructura Punto.
 * Retorna 0 si los puntos son iguales, y un valor distinto de 0 si no lo son.
 */
int comparar_puntos(void* p1, void* p2) {
  Punto* punto1 = (Punto*)p1;
  Punto* punto2 = (Punto*)p2;
  return (punto1->x == punto2->x && punto1->y == punto2->y) ? 0 : 1;
}

/**
 * Función para copiar un punto.
 * Retorna un nuevo punto con los mismos valores.
 */
void* copiar_punto(void* punto) {
  Punto* punto_original = (Punto*)punto;
  Punto* nuevo_punto = malloc(sizeof(Punto));
  assert(nuevo_punto != NULL);
  nuevo_punto->x = punto_original->x;
  nuevo_punto->y = punto_original->y;

  return nuevo_punto;
}

/**
 * Función destructora para liberar un punto.
 */
void destruir_punto(void* punto) {
  free(punto);
}
