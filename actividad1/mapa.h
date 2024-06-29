#ifndef __MAPA_H__
#define __MAPA_H__

#include "pila.h"

/**
 * Estructura de Punto para representar coordenadas
 * Tiene un valor entero x
 * Tiene un valor entero y
 */
typedef struct {
  int x, y;
} Punto;

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
 * Estructura de Mapa para representar el entorno
 * Tiene una matriz bidimensional que representa el mapa
 * Un valor entero N para las filas
 * Un valor entero M para las columnas
 * Un Punto 'robot' para representar el robot en el mapa
 * Un Punto 'final' para representar el punto de llegada
 * Una Pila 'camino' que guarda los movimientos del robot y se utiliza para backtracking
 */
typedef struct {
  char** mat;
  int N;
  int M;
  Punto robot;
  Punto final;
  Pila camino;
} _Mapa;

typedef _Mapa* Mapa;

/**
 * Devuelve un mapa con el archivo de entrada. Devuelve NULL si el archivo no existe o no es válido.
 */
Mapa mapa_crear(char[]);

/**
 * Imprime el mapa por la salida estándar.
 */
void imprimir_mapa(Mapa);

/**
 * Destruye el mapa y sus datos.
 */
void destruir_mapa(Mapa);

/**
 * Mueve el robot hacia la direccion indicada si es posible e imprime su caracter correspondiente
 * El tercer parámetro es ignorarRepetidos. En caso de que sea 1, se ignoran las casillas visitadas, sino se toman como validas
 * Devuelve 1 si fue posible el movimiento, 0 si no fue posible
 */
int move(Mapa, Direccion, int);

/**
 * Toma una direccion y devuelve su contraria para backtracking
 */
Direccion reverse(Direccion);

#endif /* __MAPA_H__ */
