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

void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) { // Libera cada fila
    free(mapa->mat[i]);
  }
  free(mapa->mat); // Libera la matriz
  free(mapa);
}
