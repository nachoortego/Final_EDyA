#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

/**
 * Crea un nuevo mapa con las dimensiones dadas y coloca el robot y el objetivo en las coordenadas especificadas.
 * 
 * @param N Número de filas del mapa.
 * @param M Número de columnas del mapa.
 * @param D Máxima distancia del sensor.
 * @param i1 Fila de la posición inicial del robot.
 * @param j1 Columna de la posición inicial del robot.
 * @param i2 Fila de la posición del objetivo.
 * @param j2 Columna de la posición del objetivo.
 * @return Un puntero al nuevo mapa creado.
 */
Mapa mapa_crear(int N, int M, int D, int i1, int j1, int i2, int j2) {
  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);
  mapa->N = N;  // Inicializa N
  mapa->M = M;  // Inicializa M
  mapa->D = D;  // Inicializa D
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

/**
 * Imprime el mapa por la salida estándar.
 * 
 * @param mapa El mapa que se desea imprimir.
 */
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

/**
 * Funcion que se pasa como parámetro a pila_destruir, no destruye el dato.
 * @param dato El dato a no destruir.
 */
void no_destruir_pila(void* dato) {}

/**
 * Funcion que se pasa como parámetro a arreglo_destruir para liberar el char*.
 * @param dato El dato a liberar.
 */
void destruir_arrego(void* dato) { free(dato); }

/**
 * Destruye el mapa y sus datos.
 * @param mapa El mapa a destruir.
 */
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


/**
 * Toma una dirección y devuelve su opuesta, utilizado para backtracking.
 * 
 * @param dir La dirección para la cual se desea obtener la opuesta.
 * @return La dirección opuesta a la proporcionada.
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
