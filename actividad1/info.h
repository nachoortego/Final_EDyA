#ifndef __INFO_H__
#define __INFO_H__

#include "punto.h"

typedef struct {
  char** mat;
  int N;
  int M;
  Punto robot;
  Punto objetivo;
} _Info;

typedef _Info* Info;

/**
 * Toma como argumento el nombre de un archivo.
 * Devuelve una estructura Infocon la informacion del archivo.
 * Devuelve NULL si el archivo no existe o no es válido.
 */
Info info_crear(char filename[]);

/**
 * Destruye la estructura info y todos sus datos.
 */
void info_destruir(Info);

#endif /* __INFO_H__ */
