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
 * @param D Máxima distancia conocida del sensor.
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
 * Inicializa las estructuras Cola y Arreglo
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
 * Mueve el robot a la posición dada y agrega su dirección al Arreglo camino.
 * Solo funciona si el punto es adyacente al robot.
 * 
 * @param mapa El mapa en el que se encuentra el robot.
 * @param nuevo La nueva posición del robot.
 */
void mover_robot(Mapa mapa, Punto dir);

/**
 * Verifica si el movimiento es válido.
 * 
 * @param mapa El mapa en el que se encuentra el robot.
 * @param nuevo El punto a analizar.
 * @return 1 si el movimiento es válido, 0 en caso contrario.
 */
int movimiento_valido(Mapa mapa, Punto dir);


#endif /* __MAPA_H__ */
