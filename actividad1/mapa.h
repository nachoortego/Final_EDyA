#ifndef __MAPA_H__
#define __MAPA_H__

/**
 * Estructura de Punto para representar coordenadas
 * Tiene un valor entero x
 * Tiene un valor entero y
 */
typedef struct {
  int x;
  int y;
} Punto;

/**
 * Estructura de Mapa para representar el entorno
 * Tiene una matriz bidimensional que representa el mapa en si
 * Un valor entero N para las filas
 * Un valor entero M para las columnas
 * Un Punto 'a' para representar el punto de partida
 * Un Punto 'b' para representar el punto de llegada
 */
typedef struct {
  char** mat;
  int N;
  int M;
  Punto a;
  Punto b;
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

#endif /* __MAPA_H__ */
