#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "mapa.h"

static void imprimir_direccion(void *dato) {
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

/**
 * Acerca al robot lo más posible al objetivo, hasta chocarse obstaculos que se lo impidan.
 * Considera las celdas visitadas como obstaculos, por eso a la funcion move se le pasa un 1. 
 */
static void camino_corto(Mapa mapa) {
  int moved = 1;
  while (moved) {
    moved = 0;
    int dx = mapa->final.x - mapa->robot.x; // Distancia x al objetivo
    int dy = mapa->final.y - mapa->robot.y; // Distancia y al objetivo

    // Prioriza movimientos segun la distancia al objetivo
    if (dx > 0 && move(mapa, RIGHT, 1)) {
      imprimir_mapa(mapa);
      moved = 1;
    } 
    else if (dx < 0 && move(mapa, LEFT, 1)) {
      imprimir_mapa(mapa);
      moved = 1;
    } 
    else if (dy > 0 && move(mapa, DOWN, 1)) {
      imprimir_mapa(mapa);
      moved = 1;
    } 
    else if (dy < 0 && move(mapa, UP, 1)) {
      imprimir_mapa(mapa);
      moved = 1;
    }
  }
}

/**
 * Comprueba si el robot llegó al objetivo. Devuelve 1 si lo logró, 0 si no.
 */
static int check_estado(Mapa mapa) {
  return mapa->robot.x == mapa->final.x && mapa->robot.y == mapa->final.y;
}

/**
 * Funcion que se pasa como parámetro a pila_desapilar, no destruye el dato.
 */
static void no_destruir(void* dir) {}

/**
 * Se mueve a una celda adyacente no visitada, independientemente de si se acerca o no al objetivo.
 */
static int buscar_no_visitados(Mapa mapa) { 
  // Arreglo de direcciones posibles
  Direccion dirs[] = { LEFT, RIGHT, UP, DOWN };

  // Itera sobre cada dirección y verifica si hay celdas sin visitar
  for(int i = 0; i < 4; i++) {
    if(move(mapa, dirs[i], 1)) {
      return 1; // Celda sin visitar encontrada
    }
  }
  return 0; // No se encontraron celdas sin visitar
}

/**
 * Dado un mapa valido, encuentra un camino al objetivo e imprime cada movimiento del robot.
 */
void encontrar_camino(Mapa mapa) {
  if(check_estado(mapa)) // Si el robot ya esta en el objetivo
    printf("Completado!\n");
  while(!check_estado(mapa)) { // Mientras el robot no este en el objetivo
    camino_corto(mapa); // Se acerca lo mas posible al objetivo
    if(!check_estado(mapa)) {
      if(buscar_no_visitados(mapa)) { // Se mueve a casillas no visitadas
        imprimir_direccion(mapa);
      }
      else{ // Si no las hay, vuelve en sus movimientos hasta que se pueda acercar nuevamente al objetivo
        Direccion retroceder = reverse((Direccion)(intptr_t) pila_tope(mapa->camino)); // Casteo explicito de void* a Direccion
        move(mapa, retroceder, 0);
        imprimir_mapa(mapa);
        mapa->camino = pila_desapilar(mapa->camino, no_destruir);
        camino_corto(mapa);
      }
    }
  }
  pila_imprimir(mapa->camino, imprimir_direccion);
  printf("\nCompletado!\n");
}
