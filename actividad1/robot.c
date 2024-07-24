#include "robot.h"
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

Robot robot_crear(Info info) {
  Robot robot = malloc(sizeof(_Robot));
  assert(robot != NULL);
  robot->pos = info->robot;
  robot->obj = info->objetivo;
  robot->camino = pila_crear();
  robot->visitados = tablahash_crear(100, copiar_punto, comparar_puntos, destruir_punto, hash_punto);
  return robot;
}

// Funcion local que toma pila_apilar como argumento, no destruye la direccion.
static void no_destruir(void* dir) {}

void destruir_robot(Robot robot) {
  pila_destruir(robot->camino, no_destruir);
  tablahash_destruir(robot->visitados);
  free(robot);
}

Direccion reverse(Direccion dir) {
  switch (dir) {
  case LEFT:
    return RIGHT;
  case RIGHT:
    return LEFT;
  case UP:
    return DOWN;
  case DOWN:
    return UP;
  default:
    return dir; // Devuelve por defecto, este caso no ocurre si dir esta bien definido
  }
}

void imprimir_direccion(void *dato) {
  Direccion dir = (Direccion)(intptr_t)dato; // Cast explícito
  switch (dir) {
    case LEFT:
      printf("L");
      break;
    case RIGHT:
      printf("R");
      break;
    case UP:
      printf("U");
      break;
    case DOWN:
      printf("D");
      break;
  }
}