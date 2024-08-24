#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

typedef struct {
  int x, y;
} Punto;

typedef struct Nodo {
  Punto punto;
  int costo;
  struct Nodo* siguiente;
} Nodo;

typedef struct {
  Nodo* frente;
  Nodo* final;
} ColaP;

typedef struct {
    char** mat;
    int N, M, D;
    Punto robot;
    Punto objetivo;
    ColaP cola;
    Arreglo camino;
} _Mapa;

typedef _Mapa* Mapa;

typedef enum { LEFT, RIGHT, UP, DOWN } Direccion;

int move(Mapa mapa, Direccion dir);
int d_star(Mapa mapa);
ColaP* crear_cola_p();
void insertar_cola_p(ColaP* cola, Punto punto, int costo);
Nodo* extraer_min_cola_p(ColaP* cola);
int obtener_costo(Mapa mapa, Punto punto);
void actualizar_costo(Mapa mapa, Punto punto, int costo);
void imprimir_mapa(Mapa mapa);
void* no_copiar(void* p);

int d_star(Mapa mapa) {
  ColaP* cola = crear_cola_p();
  insertar_cola_p(cola, mapa->objetivo, 0);

  while (cola->frente != NULL) {
    Nodo* minNodo = extraer_min_cola_p(cola);
    Punto actual = minNodo->punto;
    int costo_actual = minNodo->costo;
    free(minNodo);

    Punto vecinos[4] = {
      {actual.x - 1, actual.y},
      {actual.x + 1, actual.y},
      {actual.x, actual.y - 1},
      {actual.x, actual.y + 1}
    };

    for (int i = 0; i < 4; i++) {
      Punto vecino = vecinos[i];
      if (vecino.x >= 0 && vecino.x < mapa->M && vecino.y >= 0 && vecino.y < mapa->N) {
        if (mapa->mat[vecino.y][vecino.x] != '#' && mapa->mat[vecino.y][vecino.x] != '?') {
          int nuevo_costo = costo_actual + 1;
          if (nuevo_costo < obtener_costo(mapa, vecino)) {
            insertar_cola_p(cola, vecino, nuevo_costo);
            actualizar_costo(mapa, vecino, nuevo_costo);
          }
        }
      }
    }
  }
  return 0;
}

/**
 * Funcion local que toma arreglo_escribir como argumento. 
 * @param dato El dato a copiar.
 * @return Devuelve una copia fisica.
 */
static char* copia_direccion(char* dato) {
  char* nuevoDato = malloc(sizeof(char));
  *nuevoDato = *dato;
  return nuevoDato; // Devuelve el mismo dato sin realizar una copia
}


int move(Mapa mapa, Direccion dir) {
    char movimiento;
    int moved = 0;
    switch (dir) {
        case LEFT:
            if ((mapa->robot.x - 1) >= 0 && mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '#' &&
                mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '?') {
                mapa->robot.x--;
                movimiento = 'L';
                moved = 1;
            }
            break;
        case RIGHT:
            if ((mapa->robot.x + 1) < mapa->M && mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '#' &&
                mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '?') {
                mapa->robot.x++;
                movimiento = 'R';
                moved = 1;
            }
            break;
        case UP:
            if ((mapa->robot.y - 1) >= 0 && mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '#' &&
                mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '?') {
                mapa->robot.y--;
                movimiento = 'U';
                moved = 1;
            }
            break;
        case DOWN:
            if ((mapa->robot.y + 1) < mapa->N && mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '#' &&
                mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '?') {
                mapa->robot.y++;
                movimiento = 'D';
                moved = 1;
            }
            break;
    }
    if (moved) {
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R';
        arreglo_escribir(mapa->camino, &movimiento, (FuncionCopia) copia_direccion);
        imprimir_mapa(mapa);
        return 1;
    }
    return 0;
}

int main() {
    // Inicializar el mapa, el robot y el objetivo

    Mapa mapa = inicializar_mapa();
    d_star(mapa);  // Calcular el camino inicial

    while (mapa->robot.x != mapa->objetivo.x || mapa->robot.y != mapa->objetivo.y) {
        // Mover el robot según el camino calculado por D*
        if (!move(mapa, obtener_siguiente_direccion(mapa))) {
            // Si el movimiento falla, se detecta un nuevo obstáculo
            actualizar_mapa(mapa);  // Actualizar el mapa con la nueva información
            d_star(mapa);  // Recalcular el camino
        }
    }

    return 0;
}
