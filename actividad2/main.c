#include <stdio.h>
#include <stdlib.h>
#include "encontrar_camino.c"
#include <stdlib.h>

int main() {
  int N, M, D;
  scanf("%d%d%d", &N, &M, &D);
  int i1 , j1;
  scanf("%d%d", &i1, &j1);
  int i2 , j2;
  scanf("%d%d", &i2, &j2);

  // fprintf(stderr,"%d %d %d\n", N, M, D);
  // fprintf(stderr,"%d %d\n", i1, j1);
  // fprintf(stderr,"%d %d\n", i2, j2);
  // i1 = 2;
  // j1 = 3;

  Mapa mapa = mapa_crear(N, M, i1, j1, i2, j2);
  imprimir_mapa(mapa);
  encontrar_camino(mapa);
  destruir_mapa(mapa);

  return 0;
}