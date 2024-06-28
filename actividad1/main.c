#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <archivo>\n", argv[0]);
    exit(1);
  }

  Mapa mapa = mapa_crear(argv[1]);
  if (!mapa) {
    printf("Archivo no encontrado o no válido\n");
    exit(2);
  }

  // Probar movimientos del robot
  imprimir_mapa(mapa);
  moveDown(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveDown(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveRight(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveDown(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveUp(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveLeft(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveLeft(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveRight(mapa);
  getchar();
  imprimir_mapa(mapa);
  moveRight(mapa);
  getchar();
  imprimir_mapa(mapa);


  return 0;
}