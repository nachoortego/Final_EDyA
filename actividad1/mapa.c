#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Mapa mapa_crear(Info info) {
  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);
  mapa->N = info->N;
  mapa->M = info->M;
  mapa->mat = info->mat;

  return mapa;
}

void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      if (mapa->mat[i][j] == '#') {
        printf("\033[0;35m"); // Violeta para obstáculo
      } 
      else if (mapa->mat[i][j] == 'F') {
        printf("\033[0;32m"); // Verde para posición final
      } else {
        printf("\033[0;31m"); // Default rojo para cualquier otro caso
      }
      printf("%c ", mapa->mat[i][j]);
    }
  printf("\n");
  }
  printf("\033[0;37m\n"); // Restaura el color a blanco después del mapa
  getchar(); // Espera a que se presione Enter antes de continuar
}

void no_destruir(void* dir) {}

void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) { // Libera cada fila
    free(mapa->mat[i]);
  }
  free(mapa->mat); // Libera la matriz
  free(mapa);
}

/**
 * Funcion local que toma pila_apilar como argumento. 
 * No devuelve una copia fisica.
 */
static void* no_copiar(void* dato) {
  return dato; // Devuelve el mismo dato sin realizar una copia
}

/**
 * Mueve el robot hacia la direccion indicada si es posible e imprime su caracter correspondiente.
 * Cada movimiento nuevo es agregado a la pila del mapa.
 * En el caso utilizar la pila para backtraking, no se apilan los movimientos.
 * El tercer parámetro es ignorarRepetidos. 
 * En caso de que ignorarRepetidos sea 1, las casillas validas se consideran obstaculos.
 * En caso de que ignorarRepetidos sea 0, las casillas visitadas se consideran validas.
 * Devuelve 1 si fue posible el movimiento, 0 si no fue posible
 */
int move(Mapa mapa, Direccion dir, int ignorarRepetidos) {
  switch (dir) {
    case LEFT:
      if ((mapa->robot.x - 1) >= 0 &&
          mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.x--; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          mapa->camino = pila_apilar(mapa->camino, (void*)LEFT, no_copiar); // Apila el movimiento realizado
        printf("L\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case RIGHT:
      if ((mapa->robot.x + 1) < mapa->M &&
          mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.x++; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          mapa->camino = pila_apilar(mapa->camino, (void*)RIGHT, no_copiar ); // Apila el movimiento realizado
        printf("R\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case UP:
      if ((mapa->robot.y - 1) >= 0 &&
          mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.y--; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          mapa->camino = pila_apilar(mapa->camino, (void*)UP, no_copiar); // Apila el movimiento realizado
        printf("U\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case DOWN:
      if ((mapa->robot.y + 1) < mapa->N &&
          mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.y++; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          mapa->camino = pila_apilar(mapa->camino, (void*)DOWN, no_copiar); // Apila el movimiento realizado
        printf("D\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;
  }
  return 0; // En caso de no haberse movido
}

/**
 * Toma una direccion y devuelve su opuesta, utilizado para backtracking
 */
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
