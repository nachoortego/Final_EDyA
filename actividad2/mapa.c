#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

/**
 * Toma como argumento las dimensiones del mapa y las coordenadas del robot y el objetivo.
 * Devuelve un mapa con todas sus casillas ocupadas, y robot y objetivo ubicados en el mismo.
 */
Mapa mapa_crear(int N, int M, int i1, int j1, int i2, int j2) {
  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);
  mapa->N = N;  // Inicializa N 
  mapa->M = M;  // Inicializa M
  mapa->mat = NULL;  // Inicializa mat
  mapa->camino = NULL;  // Inicializa camino
  mapa->robot.y = i1;  // Inicializa robot.y
  mapa->robot.x = j1;  // Inicializa robot.x
  mapa->objetivo.y = i2;  // Inicializa objetivo.y
  mapa->objetivo.x = j2;  // Inicializa objetivo.x
  mapa->sensores = NULL;  // Inicializa sensores

  // Inicializar matriz
  mapa->mat = malloc(sizeof(char*) * mapa->N);
  assert(mapa->mat != NULL);
  for (int i = 0; i < mapa->N; i++) {
    mapa->mat[i] = malloc(sizeof(char) * (mapa->M + 1)); // +1 para el '\0'
    assert(mapa->mat[i] != NULL);
    for(int j = 0; j < mapa->M; j++) {
      mapa->mat[i][j] = '#'; // Marca inicialmente toda casilla como ocupada
    }
  }

  mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Escribir el robot en la matriz
  mapa->mat[mapa->objetivo.y][mapa->objetivo.x] = 'F'; // Escribir el objetivo en la matriz

  mapa->camino = pila_crear(); // Inicializar la pila

  return mapa;
}

/**
 * Imprime el mapa por la salida estándar.
 */
void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      if (mapa->mat[i][j] == '#') {
        fprintf(stderr,"\033[0;35m"); // Violeta para obstáculo
      } 
      else if (mapa->mat[i][j] == 'F') {
        fprintf(stderr,"\033[0;32m"); // Verde para posición final
      } else {
        fprintf(stderr,"\033[0;31m"); // Default rojo para cualquier otro caso
      }
      fprintf(stderr,"%c ", mapa->mat[i][j]);
    }
  fprintf(stderr,"\n");
  }
  fprintf(stderr,"\033[0;37m\n"); // Restaura el color a blanco después del mapa
  //getchar(); // Espera a que se presione Enter antes de continuar
}

/**
 * Funcion que se pasa como parámetro a pila_destruir, no destruye el dato.
 */
void no_destruir(void* dir) {}

/**
 * Destruye el mapa y sus datos.
 */
void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) { // Libera cada fila
    free(mapa->mat[i]);
  }
  free(mapa->mat); // Libera la matriz
  pila_destruir(mapa->camino, no_destruir); // Libera la pila 
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
        fprintf(stderr,"L\n");
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
        fprintf(stderr,"R\n");
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
        fprintf(stderr,"U\n");
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
        fprintf(stderr,"D\n");
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
