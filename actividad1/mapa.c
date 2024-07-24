#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Mapa mapa_crear(Info info) {
  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);
  mapa->N = info->N;
  mapa->M = info->M;
  mapa->mat = info->mat;

  return mapa;
}

void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      if (mapa->mat[i][j] == '#') {
        printf("\033[0;35m"); // Violeta para obstáculo
      } 
      else if (mapa->mat[i][j] == 'F') {
        printf("\033[0;32m"); // Verde para posición final
      } else {
        printf("\033[0;31m"); // Default rojo para cualquier otro caso
      }
      printf("%c ", mapa->mat[i][j]);
    }
  printf("\n");
  }
  printf("\033[0;37m\n"); // Restaura el color a blanco después del mapa
  getchar(); // Espera a que se presione Enter antes de continuar
}

void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) { // Libera cada fila
    free(mapa->mat[i]);
  }
  free(mapa->mat); // Libera la matriz
  free(mapa);
}
