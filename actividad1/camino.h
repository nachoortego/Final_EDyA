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

#endif /* __CAMINO_H__ */
