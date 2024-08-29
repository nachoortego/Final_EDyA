#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

Mapa mapa_crear(int N, int M, int i1, int j1, int i2, int j2) {
  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);
  mapa->N = N;  // Inicializa N
  mapa->M = M;  // Inicializa M
  mapa->D = 1;  // Inicializa D
  mapa->robot.y = i1;  // Inicializa robot.y
  mapa->robot.x = j1;  // Inicializa robot.x
  mapa->objetivo.y = i2;  // Inicializa objetivo.y
  mapa->objetivo.x = j2;  // Inicializa objetivo.x
  mapa->cola = cola_crear(mapa->N * mapa->M); // Inicializar la cola
  mapa->camino = arreglo_crear(mapa->N * mapa->M); // Inicializar el arreglo camino

  // Inicializar matriz
  mapa->mat = malloc(sizeof(char*) * mapa->N);
  assert(mapa->mat != NULL);

  // Inicializar Gscore
  mapa->gScore = (int**)malloc(mapa->N * sizeof(int*));
  assert(mapa->gScore != NULL);

  for (int i = 0; i < mapa->N; i++) {
    mapa->mat[i] = malloc(sizeof(char) * (mapa->M + 1)); // +1 para el '\0'
    assert(mapa->mat[i] != NULL);

    mapa->gScore[i] = (int*)malloc(mapa->M * sizeof(int));
    assert(mapa->gScore[i] != NULL);

    for(int j = 0; j < mapa->M; j++) {
      mapa->mat[i][j] = '.'; // Marca inicialmente toda casilla como vacia
    }
  }

  mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Escribir el robot en la matriz
  mapa->mat[mapa->objetivo.y][mapa->objetivo.x] = 'F'; // Escribir el objetivo en la matriz

  return mapa;
}

void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      if (mapa->mat[i][j] == '#') {
        fprintf(stderr,"\033[0;35m"); // Violeta para obstáculo
      } else if (mapa->mat[i][j] == '?') {
        fprintf(stderr,"\033[0;37m"); // Blanco para lugar no descubierto
      } else if (mapa->mat[i][j] == 'F') {
        fprintf(stderr,"\033[0;32m"); // Verde para posición final
      } else {
        fprintf(stderr,"\033[0;31m"); // Default rojo para cualquier otro caso
      }
      fprintf(stderr,"%c ", mapa->mat[i][j]);
    }
  fprintf(stderr,"\n");
  }
  fprintf(stderr,"\033[0;37m\n"); // Restaura el color a blanco después del mapa
}

static void destruir_arrego(void* dato) { free(dato); }

void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) { // Libera cada fila
    free(mapa->mat[i]);
    free(mapa->gScore[i]);
  }

  free(mapa->mat); // Libera la matriz
  free(mapa->gScore); // Libera gScore
  cola_destruir(mapa->cola); // Libera la cola 
  arreglo_destruir(mapa->camino, destruir_arrego); // Libera el Arreglo camino
  free(mapa);
}

/**
 * Funcion local que toma arreglo_escribir como argumento. 
 * @param dato El dato a copiar.
 * @return Devuelve una copia fisica.
 */
static char* copia_direccion(char* dato) {
  char* nuevoDato = malloc(sizeof(char));
  *nuevoDato = *dato;
  return nuevoDato; // Devuelve el mismo dato sin realizar una copia
}

int movimiento_valido(Mapa mapa, Punto nuevo, int print) {
  // Verifica que la nueva posición esté dentro de los límites del mapa
  if (nuevo.x < 0 || nuevo.x >= mapa->M || nuevo.y < 0 || nuevo.y >= mapa->N) {
    return 0; // Movimiento fuera de los límites del mapa
  }
  
  // Verifica si la nueva posición es un obstáculo o una casilla desconocida
  if (mapa->mat[nuevo.y][nuevo.x] == '#') {
    return 0; // Movimiento a una casilla no válida
  }

  if(print) 
    fprintf(stderr, "> (%d, %d) VALIDO \n", nuevo.x, nuevo.y);

  return 1; // Movimiento válido
}

void mover_robot(Mapa mapa, Punto nuevo) {
  fprintf(stderr, "> MOVER: (%d, %d) -> (%d, %d)\n", mapa->robot.y, mapa->robot.x, nuevo.y, nuevo.x);

  // Determina la dirección del movimiento
  char movimiento;
  if (nuevo.x + 1 == mapa->robot.x) {
      movimiento = 'L'; // Movimiento a la izquierda
  } else if (nuevo.x - 1 == mapa->robot.x) {
      movimiento = 'R'; // Movimiento a la derecha
  } else if (nuevo.y + 1 == mapa->robot.y) {
      movimiento = 'U'; // Movimiento hacia arriba
  } else if (nuevo.y - 1 == mapa->robot.y) {
      movimiento = 'D'; // Movimiento hacia abajo
  } else {
      return; // No hay movimiento
  }

  // Actualiza la posición del robot
  mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la antigua posición del robot
  mapa->robot.x = nuevo.x;
  mapa->robot.y = nuevo.y;
  mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Marca la nueva posición del robot

  // Registra el movimiento
  arreglo_escribir(mapa->camino, &movimiento, (FuncionCopia) copia_direccion);
}
