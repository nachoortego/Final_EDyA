#include "info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

Info info_crear(char filename[]) {
  FILE* archivo = fopen(filename, "r");
  if (archivo == NULL) 
    return NULL; // Archivo no encontrado

  Info info = malloc(sizeof(_Info));
  assert(info != NULL);
  info->N = 0;  // Inicializa N 
  info->M = 0;  // Inicializa M
  info->mat = NULL;  // Inicializa mat

  // Leer dimensiones y puntos robot y objetivo (primero y, luego x) , tambien verificar lectura y validez de los datos
  char buffer[100]; // Leer primera línea
  if (fgets(buffer, sizeof(buffer), archivo) == NULL) {
    free(info);
    fclose(archivo);
    return NULL;
  }

  // Analizar los dos primeros valores de la primera línea 
  if (sscanf(buffer, "%d%d", &info->N, &info->M) != 2 || info->N <= 0 || info->M <= 0) {
    free(info);
    fclose(archivo);
    return NULL;
  }
  // Segunda linea
  if (fscanf(archivo, "%d%d", &info->robot.y, &info->robot.x) != 2 ||
      info->robot.x < 0 || info->robot.x >= info->M || info->robot.y < 0 || info->robot.y >= info->N) {
    free(info);
    fclose(archivo);
    return NULL;
  }
  // Tercera linea
  if (fscanf(archivo, "%d%d", &info->objetivo.y, &info->objetivo.x) != 2 ||
      info->objetivo.x < 0 || info->objetivo.x >= info->M || info->objetivo.y < 0 || info->objetivo.y >= info->N) {
    free(info);
    fclose(archivo);
    return NULL;   
  }

  // Leer linea en blanco
  char line[LINE_SIZE];
  if (fgets(line, LINE_SIZE, archivo) == NULL) {
    free(info);
    fclose(archivo);
    return NULL;
  }

  // Inicializar matriz
  info->mat = malloc(sizeof(char*) * info->N);
  assert(info->mat != NULL);
  for (int i = 0; i < info->N; i++) {
    info->mat[i] = malloc(sizeof(char) * (info->M + 1)); // +1 para el '\0'
    assert(info->mat[i] != NULL);
  }

  // Verificar dimensiones y caracteres del mapa
  for (int i = 0; i < info->N; i++) {
    if (fgets(line, LINE_SIZE, archivo) == NULL || strlen(line) < info->M) {
      destruir_info(info);
      fclose(archivo);
      return NULL; 
    }

    for (int j = 0; j < info->M; j++)
      if (line[j] != '#' && line[j] != '.') {
        destruir_info(info);
        fclose(archivo);
        return NULL;
      }

    strncpy(info->mat[i], line, info->M); // Copiar los datos
    info->mat[i][info->M] = '\0'; // Asegurar la terminación de la cadena
  }
  info->mat[info->robot.y][info->robot.x] = 'R'; // Escribir el robot en la matriz
  info->mat[info->objetivo.y][info->objetivo.x] = 'F'; // Escribir el objetivo en la matriz


  fclose(archivo);
  return info;
}

void destruir_info(Info info) {
  free(info);
}