#ifndef __MAPA_H__
#define __MAPA_H__

#include "pila.h"
#include "array.h"
#include "tablahash.h"
#include "punto.h"

/**
 * Tipo de dato Direccion para representar direcciones de movimiento
 */
typedef enum {
  LEFT,   // "L"
  RIGHT,  // "R"
  UP,     // "U"
  DOWN    // "D"
} Direccion;

/**
 * Estructura de Mapa para representar el entorno.
 * 
 * @param mat Matriz bidimensional que representa el mapa.
 * @param N Número de filas del mapa.
 * @param M Número de columnas del mapa.
 * @param robot Punto que representa la ubicación del robot en el mapa.
 * @param objetivo Punto que representa el punto de llegada en el mapa.
 * @param pila Pila que guarda los movimientos del robot y se utiliza para backtracking.
 * @param camino Arreglo que guarda los movimientos del robot para enviar al sensor.
 * @param sensores TablaHash que guarda los puntos donde el robot utilizó el sensor.
 */
typedef struct {
  char** mat;
  int N;
  int M;
  Punto robot;
  Punto objetivo;
  Pila pila;
  Arreglo camino;
  TablaHash sensores;
} _Mapa;

typedef _Mapa* Mapa;

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
Mapa mapa_crear(int N, int M, int i1, int j1, int i2, int j2);

/**
 * Destruye el mapa y libera la memoria asociada.
 * 
 * @param mapa El mapa que se desea destruir.
 */
void destruir_mapa(Mapa);

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
int move(Mapa, Direccion, int ignorarRepetidos);

/**
 * Toma una dirección y devuelve su opuesta, utilizado para backtracking.
 * 
 * @param dir La dirección para la cual se desea obtener la opuesta.
 * @return La dirección opuesta a la proporcionada.
 */
Direccion reverse(Direccion);

#endif /* __MAPA_H__ */
