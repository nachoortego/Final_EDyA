#ifndef __MAPA_H__
#define __MAPA_H__

#include "pila.h"
#include "info.h"

/**
 * Estructura de Mapa para representar el entorno
 * Tiene una matriz bidimensional que representa el mapa
 * Un valor entero N para las filas
 * Un valor entero M para las columnas
 */
typedef struct {
  char** mat;
  int N;
  int M;
} _Mapa;

typedef _Mapa* Mapa;

/**
 * Toma como argumento el nombre de un archivo.
 * Devuelve un mapa con la informacion del archivo.
 * Devuelve NULL si el archivo no existe o no es válido.
 */
Mapa mapa_crear(Info);

/**
 * Imprime el mapa por la salida estándar.
 */
void imprimir_mapa(Mapa);

/**
 * Destruye el mapa y sus datos.
 */
void destruir_mapa(Mapa);

#endif /* __MAPA_H__ */