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

  Mapa mapa = mapa_crear(N, M, D, i1, j1, i2, j2);
  imprimir_mapa(mapa);
  encontrar_camino(mapa);
  destruir_mapa(mapa);

  return 0;
}