#ifndef __INFO_H__
#define __INFO_H__

#include "punto.h"
/**
 * Estructura que contiene la información del mapa.
 * 
 * @param mat Matriz que representa el mapa.
 * @param N Número de filas en el mapa.
 * @param M Número de columnas en el mapa.
 * @param robot Posición inicial del robot en el mapa.
 * @param objetivo Posición del objetivo en el mapa.
 */
typedef struct {
  char** mat;
  int N;
  int M;
  Punto robot;
  Punto objetivo;
} _Info;

typedef _Info* Info;

/**
 * Toma como argumento el nombre de un archivo y devuelve una estructura Info con la información del archivo.
 * 
 * @param filename El nombre del archivo que contiene la información.
 * @return Una estructura Info con la información del archivo, o NULL si el archivo no existe o no es válido.
 */
Info info_crear(char filename[]);

/**
 * Destruye la estructura Info y todos sus datos.
 * 
 * @param info La estructura Info a destruir.
 */
void destruir_info(Info info);

#endif /* __INFO_H__ */