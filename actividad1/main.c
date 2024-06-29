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

static void no_destruir(void* dir) {}

static void camino_corto(Mapa mapa) { // Se acerca lo más posible al objetivo hasta chocarse un obstaculo
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

static int check_estado(Mapa mapa) {
  return mapa->robot.x == mapa->final.x && mapa->robot.y == mapa->final.y;
}

static int buscar_no_visitados(Mapa mapa) { // Comprueba si hay celdas adyacentes sin visitar, aunque no se acerquen al objetivo
  if(move(mapa, LEFT, 1))
    return 1;
  if(move(mapa, RIGHT, 1))
    return 1;
  if(move(mapa, UP, 1))
    return 1;
  if(move(mapa, DOWN, 1))
    return 1;
  return 0;
}

// static int buscar_no_visitados(Mapa mapa) { // Comprueba si hay celdas adyacentes sin visitar, aunque no se acerquen al objetivo
//   Direccion dirs[] = { LEFT, RIGHT, UP, DOWN };
//   for(int i = 0; i < 4; i++) {
//     if(move(mapa, dirs[i], 1))
//       return 1;
//   }
//   return 0;
// }

void encontrar_camino(Mapa mapa) {
  if(check_estado(mapa))
    printf("Completado!\n");
  while(!check_estado(mapa)) {
    camino_corto(mapa);
    if(!check_estado(mapa)) {
      if(buscar_no_visitados(mapa)) {
        imprimir_direccion(mapa);
      }
      else{
        Direccion retroceder = reverse((Direccion)(intptr_t)pila_tope(mapa->camino));
        move(mapa, retroceder, 0);
        imprimir_mapa(mapa);
        mapa->camino = pila_desapilar(mapa->camino, no_destruir);
        camino_corto(mapa);
      }
    }
  }
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