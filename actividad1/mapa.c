#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

Mapa mapa_crear(char filename[]) {
  FILE* archivo = fopen(filename, "r");
  if (archivo == NULL) 
    return NULL; // Archivo no encontrado

  Mapa mapa = malloc(sizeof(_Mapa));

  if (fscanf(archivo, "%d%d", &mapa->N, &mapa->M) != 2 || mapa->N <= 0 || mapa->M <= 0) {
    free(mapa);
    return NULL;
  }
  if (fscanf(archivo, "%d%d", &mapa->a.x, &mapa->a.y) != 2 ||
      mapa->a.x < 0 || mapa->a.x >= mapa->N || mapa->a.y < 0 || mapa->a.y >= mapa->M) {
    free(mapa);
    return NULL;
  }
  if (fscanf(archivo, "%d%d", &mapa->b.x, &mapa->b.y) != 2 ||
    mapa->b.x < 0 || mapa->b.x >= mapa->N || mapa->b.y < 0 || mapa->b.y >= mapa->M) {
    free(mapa);
    return NULL;   
  }

  // Leer linea en blanco
  char line[LINE_SIZE];
  if (fgets(line, LINE_SIZE, archivo) == NULL) {
    free(mapa);
    return NULL;
  }

  // Inicializar matriz
  mapa->mat = malloc(sizeof(char*) * mapa->N);
  for (int i = 0; i < mapa->N; i++) {
    mapa->mat[i] = malloc(sizeof(char) * (mapa->M + 1)); // +1 para el '\0'
  }

  // Verificar dimensiones del mapa y caractres del mapa
  for (int i = 0; i < mapa->N; i++) {
    if (fgets(line, LINE_SIZE, archivo) == NULL || strlen(line) < mapa->M)  {
      destruir_mapa(mapa);
      return NULL; 
    }

    for(int j = 0; j < mapa->M; j++)
      if(line[j] != '#' && line[j] != '.') {
        destruir_mapa(mapa);
        return NULL;
      }

    strncpy(mapa->mat[i], line, mapa->M);
    mapa->mat[i][mapa->M] = '\0'; // Asegurar la terminación de la cadena
  }

  fclose(archivo);
  return mapa;
}

void imprimir_mapa(Mapa mapa) {
  printf("\033[0;35m");
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      mapa->mat[i][j] == '#' ? printf("\033[0;31m") : printf("\033[0;35m");
      printf("%c ", mapa->mat[i][j]);
    }
    printf("\n");
  }
}

void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    free(mapa->mat[i]);
  }
  free(mapa->mat);
  free(mapa);
}
