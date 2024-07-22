#include <stdio.h>
#include <stdlib.h>
#include "encontrar_camino.c"
#include <stdlib.h>

void usar_sensor(Mapa mapa) {
  int d1, d2, d3, d4;
  printf("? %d %d\n", mapa->robot.y, mapa->robot.x);
  fflush(stdout);
  scanf("%d%d%d%d", &d1, &d2, &d3,& d4);
  fprintf(stderr, "%d %d %d %d\n", d1, d2, d3, d4);

  for(int i = 1; i < d1 && (mapa->robot.y - i) >= 0 && (mapa->robot.y - i) != 'F'; i++)
    mapa->mat[mapa->robot.y - i][mapa->robot.x] = '.'; // Sensor hacia arriba

  for(int i = 1; i < d2 && (mapa->robot.x + i) >= 0 && (mapa->robot.x + i) != 'F'; i++)
    mapa->mat[mapa->robot.y + i][mapa->robot.x] = '.'; // Sensor hacia abajo

  for(int i = 1; i < d3 && (mapa->robot.x - 1) >= 0 && (mapa->robot.x - 1) != 'F'; i++)
    mapa->mat[mapa->robot.y][mapa->robot.x - i] = '.'; // Sensor hacia la izquierda

  for(int i = 1; i < d4 && (mapa->robot.x + i) < mapa->M && (mapa->robot.x + i) != 'F'; i++)
    mapa->mat[mapa->robot.y][mapa->robot.x + i] = '.'; // Sensor hacia la derecha

  imprimir_mapa(mapa);
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
  // i1 = 2;
  // j1 = 3;

  Mapa mapa = mapa_crear(N, M, i1, j1, i2, j2);
  imprimir_mapa(mapa);
  usar_sensor(mapa);
  encontrar_camino(mapa);
  destruir_mapa(mapa);

  return 0;
}