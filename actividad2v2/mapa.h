#ifndef __MAPA_H__
#define __MAPA_H__

#include "array.h"
#include "cola.h"
#include "punto.h"

/**
 * Estructura de Mapa para representar el entorno.
 * 
 * @param N Número de filas del mapa.
 * @param M Número de columnas del mapa.
 * @param D Máxima distancia del sensor.
 * @param mat Matriz bidimensional que representa el mapa.
 * @param gScore Matriz bidimensional que guarda el costo de llegar al objetivo desde cada punto.
 * @param robot Punto que representa la ubicación del robot en el mapa.
 * @param objetivo Punto que representa el punto de llegada en el mapa.
 * @param cola Cola utilizada para generar la matriz gScore.
 * @param camino Arreglo que guarda los movimientos del robot para enviar al sensor.
 */
typedef struct {
  int N;
  int M;
  int D;
  char** mat;
  int** gScore;
  Punto robot;
  Punto objetivo;
  Cola cola;
  Arreglo camino;
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

void mover_robot(Mapa mapa, Punto dir);
int movimiento_valido(Mapa mapa, Punto dir, int print);


#endif /* __MAPA_H__ */
