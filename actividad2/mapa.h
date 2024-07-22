#ifndef __MAPA_H__
#define __MAPA_H__

#include "pila.h"
#include "array.h"

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
 * Un Punto 'objetivo' para representar el punto de llegada
 * Una Pila 'pila' que guarda los movimientos del robot y se utiliza para backtracking
 * Un Arreglo 'camino' que guarda los movimientos del robot para enviar al sensor
 */
typedef struct {
  char** mat;
  int N;
  int M;
  Punto robot;
  Punto objetivo;
  Pila pila;
  Arreglo camino;
} _Mapa;

typedef _Mapa* Mapa;

/**
 * Toma como argumento las dimensiones del mapa y las coordenadas del robot y el objetivo.
 * Devuelve un mapa con todas sus casillas ocupadas, y robot y objetivo ubicados en el mismo.
 */
Mapa mapa_crear(int N, int M, int i1, int j1, int i2, int j2);

/**
 * Imprime el mapa por la salida estándar.
 */
void imprimir_mapa(Mapa);

/**
 * Destruye el mapa y sus datos.
 */
void destruir_mapa(Mapa);

/**
 * Mueve el robot hacia la direccion indicada si es posible e imprime su caracter correspondiente.
 * Cada movimiento nuevo es agregado a la pila del mapa.
 * En el caso utilizar la pila para backtraking, no se apilan los movimientos.
 * El tercer parámetro es ignorarRepetidos. 
 * En caso de que ignorarRepetidos sea 1, las casillas validas se consideran obstaculos.
 * En caso de que ignorarRepetidos sea 0, las casillas visitadas se consideran validas.
 * Devuelve 1 si fue posible el movimiento, 0 si no fue posible
 */
int move(Mapa, Direccion, int);

/**
 * Toma una direccion y devuelve su opuesta, utilizado para backtracking
 */
Direccion reverse(Direccion);

#endif /* __MAPA_H__ */
