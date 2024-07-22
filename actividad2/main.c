#include <stdio.h>
#include <stdlib.h>
#include "encontrar_camino.c"
#include <stdlib.h>

void usar_sensor(int i1, int j1, int *d1, int *d2, int *d3, int *d4) {
  printf("? %d %d\n", i1, j1);
  fflush(stdout);
  scanf("%d%d%d%d", d1, d2, d3, d4);
  fprintf(stderr, "%d %d %d %d\n", *d1, *d2, *d3, *d4);
}

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
  i1 = 2;
  j1 = 4;
  int d1, d2, d3, d4;
  usar_sensor(i1, j1, &d1, &d2, &d3, &d4);

  Mapa mapa = mapa_crear(N, M, i1, j1, i2, j2);
  imprimir_mapa(mapa);

  return 0;
}