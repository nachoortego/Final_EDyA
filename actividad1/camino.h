#ifndef __CAMINO_H__
#define __CAMINO_H__

#include "robot.h"
#include "mapa.h"

/**
 * Mueve el robot hacia la direccion indicada si es posible e imprime su caracter correspondiente.
 * Cada movimiento nuevo es agregado a la pila del mapa.
 * En el caso utilizar la pila para backtraking, no se apilan los movimientos.
 * El tercer parámetro es ignorarRepetidos. 
 * En caso de que ignorarRepetidos sea 1, las casillas validas se consideran obstaculos.
 * En caso de que ignorarRepetidos sea 0, las casillas visitadas se consideran validas.
 * Devuelve 1 si fue posible el movimiento, 0 si no fue posible
 */
int move(Mapa, Robot , Direccion, int);

/**
 * Acerca al robot lo más posible al objetivo, hasta chocarse obstaculos que se lo impidan.
 * Considera las celdas visitadas como obstaculos, por eso a la funcion move se le pasa un 1. 
 * 'priority' es una variable aleatoria que puede ser 1 o 0, y altera el eje en el que el robot se mueve.
 * De esta manera el robot no tiene peor caso, ya que su movimiento es aleatorio.
 */
void camino_corto(Mapa mapa, Robot robot);

/**
 * Comprueba si el robot llegó al objetivo. Devuelve 1 si lo logró, 0 si no.
 */
int check_estado(Robot robot);

/**
 * Se mueve a una celda adyacente no visitada, independientemente de si se acerca o no al objetivo.
 * 'priority' es una variable aleatoria que puede ser 1 o 0, y altera el eje en el que el robot se mueve.
 * De esta manera el robot no tiene peor caso, ya que su movimiento es aleatorio.
 */
int buscar_no_visitados(Mapa mapa, Robot robot);

/**
 * Dado un mapa valido, encuentra un camino al objetivo e imprime cada movimiento del robot.
 */
void encontrar_camino(Mapa mapa, Robot robot);

#endif /* __CAMINO_H__ */
