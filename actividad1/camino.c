#include "camino.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

/**
 * Funcion local que toma pila_apilar como argumento. 
 * No devuelve una copia fisica.
 */
static void* no_copiar(void* dato) {
  return dato; // Devuelve el mismo dato sin realizar una copia
}

int puede_moverse(Mapa mapa, Robot robot, Punto nuevoPunto, int ignorarRepetidos) {
  return (nuevoPunto.x >= 0 && nuevoPunto.x < mapa->M &&
          nuevoPunto.y >= 0 && nuevoPunto.y < mapa->N &&
          mapa->mat[nuevoPunto.y][nuevoPunto.x] != '#' &&
          (ignorarRepetidos == 0 || !tablahash_buscar(robot->visitados, &nuevoPunto)));
}


int move(Mapa mapa, Robot robot, Direccion dir, int ignorarRepetidos) {
  Punto nuevoPunto;
  switch (dir) {
    case LEFT:
      nuevoPunto = crear_punto(robot->pos.x - 1, robot->pos.y);
      if (puede_moverse(mapa, robot, nuevoPunto, ignorarRepetidos)) {
        tablahash_insertar(robot->visitados, &(robot->pos)); // Inserta la posicion actual en la tabla de visitados
        robot->pos.x--; // Mueve el robot a la izquierda
        mapa->mat[robot->pos.y][robot->pos.x] = 'R';
        if (ignorarRepetidos) // Si ignorarRepetidos es 1, no se apilan los movimientos
          robot->camino = pila_apilar(robot->camino, (void*)LEFT, no_copiar); 
        printf("L");
        return 1;
      }
      break;
    case RIGHT:
      nuevoPunto = crear_punto(robot->pos.x + 1, robot->pos.y);
      if (puede_moverse(mapa, robot, nuevoPunto, ignorarRepetidos)) {
        tablahash_insertar(robot->visitados, &(robot->pos)); // Inserta la posicion actual en la tabla de visitados
        robot->pos.x++; // Mueve el robot a la derecha
        mapa->mat[robot->pos.y][robot->pos.x] = 'R';
        if (ignorarRepetidos) // Si ignorarRepetidos es 1, no se apilan los movimientos
          robot->camino = pila_apilar(robot->camino, (void*)RIGHT, no_copiar);
        printf("R");
        return 1;
      }
      break;
    case UP:
      nuevoPunto = crear_punto(robot->pos.x, robot->pos.y - 1);
      if (puede_moverse(mapa, robot, nuevoPunto, ignorarRepetidos)) {
        tablahash_insertar(robot->visitados, &(robot->pos)); // Inserta la posicion actual en la tabla de visitados
        robot->pos.y--; // Mueve el robot hacia arriba
        mapa->mat[robot->pos.y][robot->pos.x] = 'R';
        if (ignorarRepetidos) // Si ignorarRepetidos es 1, no se apilan los movimientos
          robot->camino = pila_apilar(robot->camino, (void*)UP, no_copiar);
        printf("U");
        return 1;
      }
      break;
    case DOWN:
      nuevoPunto = crear_punto(robot->pos.x, robot->pos.y + 1);
      if (puede_moverse(mapa, robot, nuevoPunto, ignorarRepetidos)) {
        tablahash_insertar(robot->visitados, &(robot->pos)); // Inserta la posicion actual en la tabla de visitados
        robot->pos.y++; // Mueve el robot hacia abajo
        mapa->mat[robot->pos.y][robot->pos.x] = 'R';
        if (ignorarRepetidos) // Si ignorarRepetidos es 1, no se apilan los movimientos
          robot->camino = pila_apilar(robot->camino, (void*)DOWN, no_copiar);
        printf("D");
        return 1;
      }
    break;
  }
  return 0;
}

void camino_corto(Mapa mapa, Robot robot) {
  srand(time(NULL));
  int moved = 1;
  while (moved) {
    int priority = rand() % 2; // Eleccion aleatoria
    moved = 0;
    int dx = robot->obj.x - robot->pos.x; // Distancia x al objetivo
    int dy = robot->obj.y - robot->pos.y; // Distancia y al objetivo

    // Prioriza movimientos segun la distancia al objetivo
    if(priority) { // Si priority es 1, el robot opta por movimientos horizontales
      if (dx > 0 && move(mapa, robot, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, robot, LEFT, 1))
        moved = 1;
      else if (dy > 0 && move(mapa, robot, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, robot, UP, 1))
        moved = 1;
    }
    else { // Si priority es 0, opta por movimientos verticales
      if (dy > 0 && move(mapa, robot, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, robot, UP, 1))
        moved = 1;
      else if (dx > 0 && move(mapa, robot, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, robot, LEFT, 1))
        moved = 1;
    }
  }
}

int check_estado(Robot robot) {
  return robot->pos.x == robot->obj.x && robot->pos.y == robot->obj.y;
}

/**
 * Funcion que se pasa como parámetro a pila_desapilar, no destruye el dato.
 */
static void no_destruir(void* dir) {}

int buscar_no_visitados(Mapa mapa, Robot robot) {
  int priority = rand() % 2; // Eleccion aleatoria
  Direccion dirs[4];

  // Arreglo de direcciones posibles
  if (priority) {
    Direccion temp[] = { LEFT, RIGHT, UP, DOWN }; // Si priority es 1, el robot opta por movimientos horizontales
    for (int i = 0; i < 4; i++)
      dirs[i] = temp[i];
  } else {
    Direccion temp[] = { UP, DOWN, LEFT, RIGHT }; // Si priority es 0, opta por movimientos verticales
    for (int i = 0; i < 4; i++)
      dirs[i] = temp[i];
  }

  // Itera sobre cada dirección y verifica si hay celdas sin visitar
  for (int i = 0; i < 4; i++) 
    if (move(mapa, robot, dirs[i], 1))
      return 1; // Celda sin visitar encontrada

  return 0; // No se encontraron celdas sin visitar
}

/**
 * Dado un mapa valido, encuentra un camino al objetivo e imprime cada movimiento del robot.
 */
void encontrar_camino(Mapa mapa, Robot robot) {
  while(!check_estado(robot)) { // Mientras el robot no este en el objetivo
    camino_corto(mapa, robot); // Se acerca lo mas posible al objetivo
    if(!check_estado(robot)) { // Si no llego al objetivo
      if(buscar_no_visitados(mapa, robot)) {} // Se mueve a casillas no visitadas
      else { // Si no las hay, vuelve en sus movimientos hasta que se pueda acercar nuevamente al objetivo
        Direccion retroceder = reverse((Direccion)(intptr_t) pila_tope(robot->camino)); // Casteo explicito de void* a Direccion
        move(mapa, robot, retroceder, 0); // Retrocede usando la pila, se pasa el valor 0 a 'move' para permitir volver a casillas visitadas
        robot->camino = pila_desapilar(robot->camino, no_destruir);
      }
    }
  }
}