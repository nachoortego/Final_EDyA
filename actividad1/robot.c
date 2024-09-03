#include "robot.h"
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// Funcion local que aproxima el tamaño de la tablaHash utilizando la información del robot.
static int tamano_tablahash(Robot robot) {
  Punto max_punto;
  max_punto.x = (robot->pos.x > robot->obj.x) ? robot->pos.x : robot->obj.x;
  max_punto.y = (robot->pos.y > robot->obj.y) ? robot->pos.y : robot->obj.y;
  return (max_punto.x + 1) * (max_punto.y + 1);
}

Robot robot_crear(Info info) {
  Robot robot = malloc(sizeof(_Robot));
  assert(robot != NULL);
  robot->pos = info->robot;
  robot->obj = info->objetivo;
  robot->camino = pila_crear();
  robot->visitados = tablahash_crear(tamano_tablahash(robot), copiar_punto, comparar_puntos, destruir_punto, hash_punto);
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
