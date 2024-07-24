#include "punto.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Punto crear_punto(int x, int y) {
  Punto p;
  p.x = x;
  p.y = y;
  return p;
}

unsigned hash_punto(void* punto) {
  Punto* p = (Punto*)punto;
  return (unsigned)(p->x * 31 + p->y);
}

int comparar_puntos(void* p1, void* p2) {
  Punto* punto1 = (Punto*)p1;
  Punto* punto2 = (Punto*)p2;
  return (punto1->x == punto2->x && punto1->y == punto2->y) ? 0 : 1;
}

void* copiar_punto(void* punto) {
  Punto* punto_original = (Punto*)punto;
  Punto* nuevo_punto = malloc(sizeof(Punto));
  assert(nuevo_punto != NULL);
  nuevo_punto->x = punto_original->x;
  nuevo_punto->y = punto_original->y;

  return nuevo_punto;
}

void destruir_punto(void* punto) {
  free(punto);
}
