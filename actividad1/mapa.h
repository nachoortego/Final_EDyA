#ifndef __MAPA_H__
#define __MAPA_H__

#include "info.h"

/**
 * Estructura de Mapa para representar el entorno.
 * 
 * @param mat Matriz bidimensional que representa el mapa.
 * @param N Número de filas en el mapa.
 * @param M Número de columnas en el mapa.
 */
typedef struct {
  char** mat;
  int N;
  int M;
} _Mapa;

typedef _Mapa* Mapa;

/**
 * Toma como argumento la información del archivo y devuelve un mapa con la información del archivo.
 * 
 * @param info La información del archivo.
 * @return Mapa Un mapa con la información del archivo, o NULL si el archivo no existe o no es válido.
 */
Mapa mapa_crear(Info info);

/**
 * Destruye el mapa y sus datos.
 * 
 * @param mapa El mapa a destruir.
 */
void destruir_mapa(Mapa mapa);

#endif /* __MAPA_H__ */