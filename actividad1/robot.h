#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "pila.h"
#include "punto.h"
#include "tablahash.h"
#include "info.h"

/**
 * Estructura de Robot para representar el robot.
 * 
 * @param pos Un Punto para representar la posición actual del robot en el mapa.
 * @param obj Un Punto para representar el punto de llegada.
 * @param camino Una Pila que guarda los movimientos del robot y se utiliza para backtracking.
 * @param visitados Una TablaHash que guarda los puntos visitados por el robot.
 */
typedef struct {
  Punto pos;
  Punto obj;
  Pila camino;
  TablaHash visitados;
} _Robot;

typedef _Robot* Robot;

/**
 * Tipo de dato Direccion para representar direcciones de movimiento.
 */
typedef enum {
  LEFT,   // "L"
  RIGHT,  // "R"
  UP,     // "U"
  DOWN    // "D"
} Direccion;

/**
 * Crea un robot a partir de la información proporcionada.
 * 
 * @param info Un dato de tipo Info que contiene la información del archivo.
 * @return Robot Un dato de tipo Robot con la información del archivo.
 */
Robot robot_crear(Info info);

/**
 * Destruye el robot y sus datos.
 * 
 * @param robot El robot a destruir.
 */
void destruir_robot(Robot robot);

/**
 * Toma una dirección y devuelve su opuesta, utilizado para backtracking.
 * 
 * @param dir La dirección a invertir.
 * @return Direccion La dirección opuesta.
 */
Direccion reverse(Direccion dir);

#endif /* __ROBOT_H__ */