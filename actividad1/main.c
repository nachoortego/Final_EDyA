#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

static void imprimir_direccion(void *dato) {
  Direccion dir = (Direccion)(intptr_t)dato; // Cast explícito
  switch (dir) {
    case LEFT:
      printf("L");
      break;
    case RIGHT:
      printf("R");
      break;
    case UP:
      printf("U");
      break;
    case DOWN:
      printf("D");
      break;
  }
}

void camino_corto(Mapa mapa) { // Se acerca lo más posible al objetivo hasta chocarse un obstaculo
  int moved = 1;
  while (moved) {
    moved = 0;
    while (mapa->robot.x > mapa->final.x && move(mapa, LEFT, 1)) { // Va a la izquierda lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
    while (mapa->robot.y > mapa->final.y && move(mapa, UP, 1)) { // Va hacia arriba lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
    while (mapa->robot.x < mapa->final.x && move(mapa, RIGHT, 1)) { // Va a la derecha lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
    while (mapa->robot.y < mapa->final.y && move(mapa, DOWN, 1)) { // Va hacia abajo lo mas posible
      imprimir_mapa(mapa);
      moved = 1;
    }
  }
}

void encontrar_camino(Mapa mapa) {
  if(mapa->robot.x == mapa->final.x && mapa->robot.y == mapa->final.y)
    printf("Completado!\n");
  // while(mapa->robot.x != mapa->final.x || mapa->robot.y != mapa->final.y) {
  //   camino_corto(mapa);
  //   pila_imprimir(mapa->camino, imprimir_direccion);
  // }
  camino_corto(mapa);
  pila_imprimir(mapa->camino, imprimir_direccion);
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