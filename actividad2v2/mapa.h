#ifndef __MAPA_H__
#define __MAPA_H__

#include "cola.h"
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
 * @param D Máxima distancia del sensor.
 * @param robot Punto que representa la ubicación del robot en el mapa.
 * @param objetivo Punto que representa el punto de llegada en el mapa.
 * @param cola ColaP utilizado para D*.
 * @param camino Arreglo que guarda los movimientos del robot para enviar al sensor.
 * @param sensores TablaHash que guarda los puntos donde el robot utilizó el sensor.
 */
typedef struct {
  int N;
  int M;
  int D;
  char** mat;
  int** gScore;
  Punto robot;
  Punto objetivo;
  ColaP cola;
  Arreglo camino;
  TablaHash sensores;
} _Mapa;

typedef _Mapa* Mapa;

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
Mapa mapa_crear(int N, int M, int D, int i1, int j1, int i2, int j2);

/**
 * Imprime el mapa por la salida estándar.
 * 
 * @param mapa El mapa que se desea imprimir.
 */
void imprimir_mapa(Mapa);

/**
 * Destruye el mapa y libera la memoria asociada.
 * 
 * @param mapa El mapa que se desea destruir.
 */
void destruir_mapa(Mapa);

/**
 * Toma una dirección y devuelve su opuesta, utilizado para backtracking.
 * 
 * @param dir La dirección para la cual se desea obtener la opuesta.
 * @return La dirección opuesta a la proporcionada.
 */
Direccion reverse(Direccion);

void mover_robot(Mapa mapa, Punto dir);
int movimiento_valido(Mapa mapa, Punto dir, int print);


#endif /* __MAPA_H__ */
