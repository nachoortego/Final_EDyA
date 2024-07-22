#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>
#include "mapa.h"

__attribute__((unused)) static void imprimir_direccion(void *dato) {
  Direccion dir = (Direccion)(intptr_t)dato; // Cast explícito
  switch (dir) {
    case LEFT:
      fprintf(stderr,"L");
      break;
    case RIGHT:
      fprintf(stderr,"R");
      break;
    case UP:
      fprintf(stderr,"U");
      break;
    case DOWN:
      fprintf(stderr,"D");
      break;
  }
}

/**
 * Acerca al robot lo más posible al objetivo, hasta chocarse obstaculos que se lo impidan.
 * Considera las celdas visitadas como obstaculos, por eso a la funcion move se le pasa un 1. 
 * 'priority' es una variable aleatoria que puede ser 1 o 0, y altera el eje en el que el robot se mueve.
 * De esta manera el robot no tiene peor caso, ya que su movimiento es aleatorio.
 */
static void camino_corto(Mapa mapa) {
  srand(time(NULL));
  int moved = 1;
  while (moved) {
    int priority = rand() % 2;
    moved = 0;
    int dx = mapa->objetivo.x - mapa->robot.x; // Distancia x al objetivo
    int dy = mapa->objetivo.y - mapa->robot.y; // Distancia y al objetivo

    // Prioriza movimientos segun la distancia al objetivo
    if(priority) { // Si priority es 1, el robot opta por movimientos horizontales
      if (dx > 0 && move(mapa, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, LEFT, 1))
        moved = 1;
      else if (dy > 0 && move(mapa, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, UP, 1))
        moved = 1;
    }
    else { // Si priority es 0, opta por movimientos verticales
      if (dy > 0 && move(mapa, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, UP, 1))
        moved = 1;
      else if (dx > 0 && move(mapa, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, LEFT, 1))
        moved = 1;
    }
  }
}

/**
 * Comprueba si el robot llegó al objetivo. Devuelve 1 si lo logró, 0 si no.
 */
static int check_estado(Mapa mapa) {
  return mapa->robot.x == mapa->objetivo.x && mapa->robot.y == mapa->objetivo.y;
}

/**
 * Funcion que se pasa como parámetro a pila_desapilar, no destruye el dato.
 */
static void no_destruir(void* dir) {}

/**
 * Se mueve a una celda adyacente no visitada, independientemente de si se acerca o no al objetivo.
 * 'priority' es una variable aleatoria que puede ser 1 o 0, y altera el eje en el que el robot se mueve.
 * De esta manera el robot no tiene peor caso, ya que su movimiento es aleatorio.
 */
static int buscar_no_visitados(Mapa mapa) {
  int priority = rand() % 2; // Eleccion aleatoria
  Direccion dirs[4];

  // Arreglo de direcciones posibles
  if (priority) {
    Direccion temp[] = { LEFT, RIGHT, UP, DOWN }; // Si priority es 1, el robot opta por movimientos horizontales
    for (int i = 0; i < 4; i++) {
      dirs[i] = temp[i];
    }
  } else {
    Direccion temp[] = { UP, DOWN, LEFT, RIGHT }; // Si priority es 0, opta por movimientos verticales
    for (int i = 0; i < 4; i++) {
        dirs[i] = temp[i];
    }
  }

  // Itera sobre cada dirección y verifica si hay celdas sin visitar
  for (int i = 0; i < 4; i++) {
    if (move(mapa, dirs[i], 1)) {
      return 1; // Celda sin visitar encontrada
    }
  }
  return 0; // No se encontraron celdas sin visitar
}

/*
 * Función que se encarga de usar el sensor y actualizar el mapa.
*/
void usar_sensor(Mapa mapa) {
  int d1, d2, d3, d4;
  printf("? %d %d\n", mapa->robot.y, mapa->robot.x);
  fflush(stdout);
  scanf("%d%d%d%d", &d1, &d2, &d3,& d4);
  fprintf(stderr, "SENSOR: %d %d %d %d\n", d1, d2, d3, d4);

  for(int i = 1; i < d1; i++)
    if((mapa->mat[mapa->robot.y - i][mapa->robot.x] != '_') && (mapa->mat[mapa->robot.y - i][mapa->robot.x] != 'F'))
      mapa->mat[mapa->robot.y - i][mapa->robot.x] = '.'; // Sensor hacia arriba

  for(int i = 1; i < d2; i++)
    if((mapa->mat[mapa->robot.y + i][mapa->robot.x] != '_') && (mapa->mat[mapa->robot.y + i][mapa->robot.x] != 'F'))
      mapa->mat[mapa->robot.y + i][mapa->robot.x] = '.'; // Sensor hacia abajo

  for(int i = 1; i < d3; i++)
    if((mapa->mat[mapa->robot.y][mapa->robot.x - i] != '_') && (mapa->mat[mapa->robot.y][mapa->robot.x - i] != 'F'))
      mapa->mat[mapa->robot.y][mapa->robot.x - i] = '.'; // Sensor hacia la izquierda

  for(int i = 1; i < d4; i++)
    if((mapa->mat[mapa->robot.y][mapa->robot.x + i] != '_') && (mapa->mat[mapa->robot.y][mapa->robot.x + i] != 'F'))
      mapa->mat[mapa->robot.y][mapa->robot.x + i] = '.'; // Sensor hacia la derecha

  imprimir_mapa(mapa);
}

/**
 * Dado un mapa valido, encuentra un camino al objetivo e imprime cada movimiento del robot.
 */
void encontrar_camino(Mapa mapa) {
  if(check_estado(mapa)) { // Si el robot ya esta en el objetivo
    printf("! \n");
    fflush(stdout);
  }

  usar_sensor(mapa); // Usa el sensor por primera vez para revelar el mapa
  while(!check_estado(mapa)) { // Mientras el robot no este en el objetivo
    camino_corto(mapa); // Se acerca lo mas posible al objetivo
    if(!check_estado(mapa)) {
      usar_sensor(mapa); // Usa el sensor para actualizar el mapa
      if(buscar_no_visitados(mapa)) {} // Se mueve a casillas no visitadas
      else { // Si no las hay, vuelve en sus movimientos hasta que se pueda acercar nuevamente al objetivo
        Direccion retroceder = reverse((Direccion)(intptr_t) pila_tope(mapa->pila)); // Casteo explicito de void* a Direccion
        move(mapa, retroceder, 0); // Retrocede usando la pila, se pasa el valor 0 a 'move' para permitir volver a casillas visitadas
        mapa->pila = pila_desapilar(mapa->pila, no_destruir);
      }
    }
  }
  /*! BORRAR: pila_recorrer(mapa->pila, imprimir_direccion); */
  printf("! DDDRRU\n");
  fflush(stdout);
}