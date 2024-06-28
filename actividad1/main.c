#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void encontrar_camino(Mapa mapa) {
  if(mapa->robot.x == mapa->final.x && mapa->robot.y == mapa->final.y)
    return;
  while(mapa->robot.x < mapa->final.x && moveRight(mapa)) // Mientras se acerce y pueda ir a la derecha, que vaya
    imprimir_mapa(mapa);
  while(mapa->robot.y < mapa->final.y && moveDown(mapa))
    imprimir_mapa(mapa);
  while(mapa->robot.y >= 0 && !moveDown(mapa) && moveLeft(mapa))
    imprimir_mapa(mapa);
}

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
  imprimir_mapa(mapa);
  encontrar_camino(mapa);

  // Probar movimientos del robot
  // imprimir_mapa(mapa);
  // moveDown(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveDown(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveRight(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveDown(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveUp(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveLeft(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveLeft(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveRight(mapa);
  // getchar();
  // imprimir_mapa(mapa);
  // moveRight(mapa);
  // getchar();
  // imprimir_mapa(mapa);


  return 0;
}