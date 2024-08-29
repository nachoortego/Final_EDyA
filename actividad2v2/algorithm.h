#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "mapa.h"

/**
 * Lanza rayos en las 4 direcciones para detectar muros y actualiza el mapa.
 *
 * @param mapa El mapa en el que se encuentra el robot.
 * @param origen El punto de origen del sensor.
 * @param d1 Distancia detectada hacia arriba.
 * @param d2 Distancia detectada hacia abajo.
 * @param d3 Distancia detectada hacia la izquierda.
 * @param d4 Distancia detectada hacia la derecha.
 * @return 1 si se detectó al menos un muro, 0 en caso contrario.
 */
int lanzar_rayos(Mapa mapa, Punto origen, int d1, int d2, int d3, int d4);

/**
 * Calcula el valor máximo de los rayos detectados en las 4 direcciones.
 *
 * @param d1 Distancia detectada hacia arriba.
 * @param d2 Distancia detectada hacia abajo.
 * @param d3 Distancia detectada hacia la izquierda.
 * @param d4 Distancia detectada hacia la derecha.
 * @param d_max Valor máximo actual de la distancia de detección.
 * @return El valor máximo de las distancias de detección.
 */
int max_rayos(int d1, int d2, int d3, int d4, int d_max);

/**
 * Usa el sensor para actualizar el mapa en la posición actual del robot.
 * Obtiene la información del sensor y actualiza el mapa si el sensor no ha sido utilizado
 * en la posición actual.
 *
 * @param mapa El mapa en el que se encuentra el robot.
 * @return 1 si el sensor fue usado y el mapa fue actualizado, 0 si el sensor ya había sido usado en esa posición.
 */
int usar_sensor(Mapa mapa);

/**
 * Genera el g-score de cada punto del mapa usando un algoritmo de búsqueda basado en el objetivo.
 *
 * @param mapa El mapa en el que se encuentra el robot.
 */
void generar_g_score(Mapa mapa);

/**
 * Muestra el g-score del mapa en stderr para depuración.
 *
 * @param mapa El mapa en el que se encuentra el robot.
 */
void mostrar_g_score(Mapa mapa);

/**
 * Determina si un vecino es desconocido en el mapa (es decir, no es un muro ni el objetivo).
 *
 * @param mapa El mapa en el que se encuentra el robot.
 * @param vecino El punto vecino que se va a verificar.
 * @return 1 si el vecino es desconocido, 0 en caso contrario.
 */
int vecino_desconocido(Mapa mapa, Punto vecino);

/**
 * Verifica si el robot ha llegado al objetivo.
 *
 * @param mapa El mapa en el que se encuentra el robot.
 * @return 1 si el robot ha llegado al objetivo, 0 en caso contrario.
 */
int robot_ha_llegado(Mapa mapa);

/**
 * Algoritmo principal de búsqueda de caminos que utiliza el sensor para explorar el mapa
 * y encontrar el camino más corto hacia el objetivo.
 *
 * @param mapa El mapa en el que se encuentra el robot.
 */
void path_finding(Mapa mapa);

/**
 * Envía el camino recorrido al sensor.
 *
 * @param mapa El mapa que contiene el camino que se desea enviar.
 */
void enviar_camino(Mapa mapa);

#endif // ALGORITMO_H
