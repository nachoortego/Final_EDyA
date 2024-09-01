#ifndef __CAMINO_H__
#define __CAMINO_H__

#include "robot.h"
#include "mapa.h"

/**
 * Verifica si el robot puede moverse a una nueva posición.
 * Comprueba límites del mapa y si la celda es un obstáculo o ya fue visitada.
 * 
 * @param mapa El mapa en el que se mueve el robot.
 * @param robot El robot que se va a mover.
 * @param nuevoPunto La nueva posición a la que se quiere mover el robot.
 * @param ignorarRepetidos Indica si se deben ignorar las celdas ya visitadas.
 * @return int Devuelve 1 si el robot puede moverse a la nueva posición, 0 si no.
 */
int puede_moverse(Mapa mapa, Robot robot, Punto nuevoPunto, int ignorarRepetidos);

/**
 * Mueve el robot hacia la dirección indicada si es posible e imprime su caracter correspondiente.
 * Cada movimiento nuevo es agregado a la pila del mapa.
 * En el caso utilizar la pila para backtracking, no se apilan los movimientos.
 * 
 * @param mapa El mapa en el que se encuentra el robot.
 * @param robot El robot que se va a mover.
 * @param direccion La dirección hacia la que se va a mover el robot.
 * @param ignorarRepetidos Indica si se deben considerar las casillas visitadas como obstáculos (1) o como casillas válidas (0).
 * 
 * @return 1 si fue posible el movimiento, 0 si no fue posible.
 */
int move(Mapa mapa, Robot robot, Direccion direccion, int ignorarRepetidos);

/**
 * Acerca al robot lo más posible al objetivo, hasta chocarse obstaculos que se lo impidan.
 * Considera las celdas visitadas como obstaculos, por eso a la funcion move se le pasa un 1. 
 * 'priority' es una variable aleatoria que puede ser 1 o 0, y altera el eje en el que el robot se mueve.
 * 
 * @param mapa El mapa en el que se encuentra el robot.
 * @param robot El robot que se va a mover.
 */
void camino_corto(Mapa mapa, Robot robot);

/**
 * Comprueba si el robot llegó al objetivo.
 * 
 * @param robot El robot cuya posición se va a comprobar.
 * @return Devuelve 1 si el robot llegó al objetivo, 0 si no.
 */
int check_estado(Robot robot);

/**
 * Mueve al robot a una celda adyacente no visitada, independientemente de si se acerca o no al objetivo.
 * 
 * @param mapa El mapa en el que se encuentra el robot.
 * @param robot El robot que se va a mover.
 * @return Devuelve 1 si se movió a una celda no visitada, 0 si no.
 */
int buscar_no_visitados(Mapa mapa, Robot robot);

/**
 * Dado un mapa valido, encuentra un camino al objetivo e imprime cada movimiento del robot.
 * 
 * @param mapa El mapa en el que se mueve el robot.
 * @param robot El robot que se mueve en el mapa.
 */
void encontrar_camino(Mapa mapa, Robot robot);

#endif /* __CAMINO_H__ */
