#include "robot.h"
#include <stdlib.h>
#include <assert.h>

Robot robot_crear(Info info) {
  Robot robot = malloc(sizeof(_Robot));
  assert(robot != NULL);
  robot->pos = info->robot;
  robot->obj = info->objetivo;
  robot->camino = pila_crear();
  robot->visitados = tablahash_crear(100, copiar_punto, comparar_puntos, destruir_punto, hash_punto);
  return robot;
}
