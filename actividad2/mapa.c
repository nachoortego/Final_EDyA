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
 * @param i1 Fila de la posición inicial del robot.
 * @param j1 Columna de la posición inicial del robot.
 * @param i2 Fila de la posición del objetivo.
 * @param j2 Columna de la posición del objetivo.
 * @return Un puntero al nuevo mapa creado.
 */
Mapa mapa_crear(int N, int M, int i1, int j1, int i2, int j2) {
  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);
  mapa->N = N;  // Inicializa N 
  mapa->M = M;  // Inicializa M
  mapa->robot.y = i1;  // Inicializa robot.y
  mapa->robot.x = j1;  // Inicializa robot.x
  mapa->objetivo.y = i2;  // Inicializa objetivo.y
  mapa->objetivo.x = j2;  // Inicializa objetivo.x
  mapa->pila = pila_crear(); // Inicializar la pila
  mapa->camino = arreglo_crear(mapa->N * mapa->M); // Inicializar el arreglo camino
  mapa->sensores = tablahash_crear((mapa->N * mapa->M) / 2, copiar_punto, comparar_puntos, destruir_punto, hash_punto); // Inicializar la tabla de sensores

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

  return mapa;
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
  }
  free(mapa->mat); // Libera la matriz
  pila_destruir(mapa->pila, no_destruir_pila); // Libera la pila 
  arreglo_destruir(mapa->camino, destruir_arrego); // Libera el Arreglo camino
  tablahash_destruir(mapa->sensores); // Libera la tabla de sensores
  free(mapa);
}

/**
 * Funcion local que toma pila_apilar como argumento. 
 * @param dato El dato a copiar.
 * @return No devuelve una copia fisica.
 */
static void* no_copiar(void* dato) {
  return dato; // Devuelve el mismo dato sin realizar una copia
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

/**
 * Mueve el robot hacia la dirección indicada si es posible e imprime su carácter correspondiente.
 * Cada movimiento nuevo es agregado a la pila del mapa. 
 * Cada movimiento es agregado al arreglo camino.
 * En el caso de utilizar la pila para backtracking, no se apilan los movimientos.
 * 
 * @param mapa El mapa en el que se realiza el movimiento.
 * @param dir La dirección hacia la cual mover el robot.
 * @param ignorarRepetidos Indica si se deben considerar las casillas visitadas como válidas (0) o como obstáculos (1).
 * @return 1 si el movimiento fue posible, 0 si no fue posible.
 */
int move(Mapa mapa, Direccion dir, int ignorarRepetidos) {
  char movimiento;
  switch (dir) {
    case LEFT:
      if ((mapa->robot.x - 1) >= 0 &&
          mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.x--; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          mapa->pila = pila_apilar(mapa->pila, (void*)LEFT, no_copiar); // Apila el movimiento realizado
        
        movimiento = 'L';
        arreglo_escribir(mapa->camino,&movimiento, (FuncionCopia) copia_direccion);
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
          mapa->pila = pila_apilar(mapa->pila, (void*)RIGHT, no_copiar ); // Apila el movimiento realizado
        
        movimiento = 'R';
        arreglo_escribir(mapa->camino,&movimiento, (FuncionCopia) copia_direccion);
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
          mapa->pila = pila_apilar(mapa->pila, (void*)UP, no_copiar); // Apila el movimiento realizado
        
        movimiento = 'U';
        arreglo_escribir(mapa->camino,&movimiento, (FuncionCopia) copia_direccion);
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
          mapa->pila = pila_apilar(mapa->pila, (void*)DOWN, no_copiar); // Apila el movimiento realizado
        
        movimiento = 'D';
        arreglo_escribir(mapa->camino,&movimiento, (FuncionCopia) copia_direccion);
        return 1;
      }
      break;
  }
  return 0; // En caso de no haberse movido
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
