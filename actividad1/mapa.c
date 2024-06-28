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

  // Leer dimensiones y puntos a y b (primero y, luego x) , tambien verificar lectura y validez de los datos
  if (fscanf(archivo, "%d%d", &mapa->N, &mapa->M) != 2 || mapa->N <= 0 || mapa->M <= 0) {
    free(mapa);
    fclose(archivo);
    return NULL;
  }
  if (fscanf(archivo, "%d%d", &mapa->robot.y, &mapa->robot.x) != 2 ||
      mapa->robot.x < 0 || mapa->robot.x >= mapa->M || mapa->robot.y < 0 || mapa->robot.y >= mapa->N) {
    free(mapa);
    fclose(archivo);
    return NULL;
  }
  if (fscanf(archivo, "%d%d", &mapa->final.y, &mapa->final.x) != 2 ||
      mapa->final.x < 0 || mapa->final.x >= mapa->M || mapa->final.y < 0 || mapa->final.y >= mapa->N) {
    free(mapa);
    fclose(archivo);
    return NULL;   
  }

  // Leer linea en blanco
  char line[LINE_SIZE];
  if (fgets(line, LINE_SIZE, archivo) == NULL) {
    free(mapa);
    fclose(archivo);
    return NULL;
  }

  // Inicializar matriz
  mapa->mat = malloc(sizeof(char*) * mapa->N);
  for (int i = 0; i < mapa->N; i++) {
    mapa->mat[i] = malloc(sizeof(char) * (mapa->M + 1)); // +1 para el '\0'
  }

  // Verificar dimensiones del mapa y caracteres del mapa
  for (int i = 0; i < mapa->N; i++) {
    if (fgets(line, LINE_SIZE, archivo) == NULL || strlen(line) < mapa->M) {
      destruir_mapa(mapa);
      fclose(archivo);
      return NULL; 
    }

    for (int j = 0; j < mapa->M; j++)
      if (line[j] != '#' && line[j] != '.') {
        destruir_mapa(mapa);
        fclose(archivo);
        return NULL;
      }

    strncpy(mapa->mat[i], line, mapa->M); // Copiar los datos
    mapa->mat[i][mapa->M] = '\0'; // Asegurar la terminación de la cadena
  }
  mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Escribir el robot en la matriz
  mapa->mat[mapa->final.y][mapa->final.x] = 'F'; // Escribir el final en la matriz

  fclose(archivo);
  return mapa;
}


void imprimir_mapa(Mapa mapa) {
  printf("\033[0;31m"); // rojo
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      mapa->mat[i][j] == '#' ? printf("\033[0;35m") : printf("\033[0;31m"); // violeta o rojo
      printf("%c ", mapa->mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    free(mapa->mat[i]);
  }
  free(mapa->mat);
  free(mapa);
}

void moveRight(Mapa mapa) {
  if ((mapa->robot.x + 1) < mapa->M && mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '#') {
    mapa->mat[mapa->robot.y][mapa->robot.x] = '.';
    mapa->robot.x++;
    mapa->mat[mapa->robot.y][mapa->robot.x] = 'R';
    printf("R");
  }
}

void moveLeft(Mapa mapa) {
  if ((mapa->robot.x - 1) >= 0 && mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '#') {
    mapa->mat[mapa->robot.y][mapa->robot.x] = '.';
    mapa->robot.x--;
    mapa->mat[mapa->robot.y][mapa->robot.x] = 'R';
    printf("L");
  }
}

void moveUp(Mapa mapa) {
  if ((mapa->robot.y - 1) >= 0 && mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '#') {
    mapa->mat[mapa->robot.y][mapa->robot.x] = '.';
    mapa->robot.y--;
    mapa->mat[mapa->robot.y][mapa->robot.x] = 'R';
    printf("U");
  }
}

void moveDown(Mapa mapa) {
  if ((mapa->robot.y + 1) < mapa->N && mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '#') {
    mapa->mat[mapa->robot.y][mapa->robot.x] = '.';
    mapa->robot.y++;
    mapa->mat[mapa->robot.y][mapa->robot.x] = 'R';
    printf("D");
  }
}