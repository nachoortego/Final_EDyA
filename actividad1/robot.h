#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "pila.h"
#include "punto.h"
#include "tablahash.h"
#include "info.h"

/**
 * Estructura de Robot para representar el robot
 * 
 * Un Punto 'robot' para representar el robot en el mapa
 * Un Punto 'obj' para representar el punto de llegada
 * Una Pila 'camino' que guarda los movimientos del robot y se utiliza para backtracking
 * Una TablaHash 'visitados' que guarda los puntos visitados por el robot
 */
typedef struct {
  Punto pos;
  Punto obj;
  Pila camino;
  TablaHash visitados;
} _Robot;

typedef _Robot* Robot;

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
 * Toma como argumento el nombre de un archivo.
 * Devuelve un mapa con la informacion del archivo.
 * Devuelve NULL si el archivo no existe o no es válido.
 */
Robot robot_crear(Info);

/**
 * Destruye el robot y sus datos.
 */
void destruir_robot(Robot);

/**
 * Toma una direccion y devuelve su opuesta, utilizado para backtracking
 */
Direccion reverse(Direccion);

#endif /* __ROBOT_H__ */
