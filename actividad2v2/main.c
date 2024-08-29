#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "algorithm.h"

#define INT_MAX 99 //2147483647

int main() {
  int N, M;
  scanf("%d%d%*d", &N, &M);
  int i1 , j1;
  scanf("%d%d", &i1, &j1);
  int i2 , j2;
  scanf("%d%d", &i2, &j2);

  Mapa mapa = mapa_crear(N, M, i1, j1, i2, j2);

  path_finding(mapa);

  imprimir_mapa(mapa);
  enviar_camino(mapa);
  destruir_mapa(mapa);

  return 0;
}