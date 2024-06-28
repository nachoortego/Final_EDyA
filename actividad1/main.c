#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void camino_corto(Mapa mapa) { // Se acerca lo más posible al objetivo hasta chocarse un obstaculo
  int moved = 1;
  while (moved) {
    moved = 0;
    while (mapa->robot.x > mapa->final.x && moveLeft(mapa)) { // Va a la izquierda lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
    while (mapa->robot.y > mapa->final.y && moveUp(mapa)) { // Va hacia arriba lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
    while (mapa->robot.x < mapa->final.x && moveRight(mapa)) { // Va a la derecha lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
    while (mapa->robot.y < mapa->final.y && moveDown(mapa)) { // Va hacia abajo lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
  }
}

void encontrar_camino(Mapa mapa) {
  if(mapa->robot.x == mapa->final.x && mapa->robot.y == mapa->final.y)
    return;
  while(mapa->robot.x != mapa->final.x || mapa->robot.y != mapa->final.y) {
    camino_corto(mapa);
  }
  printf("Completado!\n");
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
  destruir_mapa(mapa);

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