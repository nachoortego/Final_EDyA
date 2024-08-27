#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "mapa.h"

#define INT_MAX 2147483647

/**
 * Usa el sensor para actualizar el mapa en la posición actual del robot.
 * 
 * Si el sensor nunca ha sido utilizado en la posición actual, se obtiene la
 * información del sensor y se actualiza el mapa en las direcciones correspondientes.
 * 
 * @param mapa El mapa en el que se encuentra el robot.
 * @return 1 si el sensor fue usado y el mapa fue actualizado, 0 si el sensor ya había sido usado en esa posición.
 */
int usar_sensor(Mapa mapa) {
  if (!tablahash_buscar(mapa->sensores, &mapa->robot)) { // Si el sensor nunca fue utilizado en esa posición
    int d1, d2, d3, d4;
    printf("? %d %d\n", mapa->robot.y, mapa->robot.x);
    fflush(stdout);
    scanf("%d%d%d%d", &d1, &d2, &d3, &d4);
    fprintf(stderr, "> SENSOR: %d %d %d %d\n", d1, d2, d3, d4);

    for(int i = 1; i < d1; i++){
      if(mapa->mat[mapa->robot.y - i][mapa->robot.x] != 'F')
        mapa->mat[mapa->robot.y - i][mapa->robot.x] = '.'; // Sensor hacia arriba
    }

    if(d1 <= mapa->D && (mapa->robot.y - d1) >= 0)
      mapa->mat[mapa->robot.y - d1][mapa->robot.x] = '#'; // Marca la casilla final

    for(int i = 1; i < d2; i++)
      if(mapa->mat[mapa->robot.y + i][mapa->robot.x] != 'F')
        mapa->mat[mapa->robot.y + i][mapa->robot.x] = '.'; // Sensor hacia abajo

    if(d2 <= mapa->D && (mapa->robot.y + d2) < mapa->N)
      mapa->mat[mapa->robot.y + d2][mapa->robot.x] = '#'; // Marca la casilla final

    for(int i = 1; i < d3; i++)
      if(mapa->mat[mapa->robot.y][mapa->robot.x - i] != 'F')
        mapa->mat[mapa->robot.y][mapa->robot.x - i] = '.'; // Sensor hacia la izquierda

    if(d3 <= mapa->D && (mapa->robot.x - d3) >= 0)
      mapa->mat[mapa->robot.y][mapa->robot.x - d3] = '#'; // Marca la casilla final

    for(int i = 1; i < d4; i++)
      if(mapa->mat[mapa->robot.y][mapa->robot.x + i] != 'F')
        mapa->mat[mapa->robot.y][mapa->robot.x + i] = '.'; // Sensor hacia la derecha
    
    if(d4 <= mapa->D && (mapa->robot.x + d4) < mapa->M)
      mapa->mat[mapa->robot.y][mapa->robot.x + d4] = '#'; // Marca la casilla final

    tablahash_insertar(mapa->sensores, &mapa->robot); // Inserta el punto en la tabla de sensores
    imprimir_mapa(mapa);
    return 1;
  }
  return 0;
}

// Arrays para mapeo de movimientos
int dx[] = {0, 0, -1, 1};  // LEFT, RIGHT, UP, DOWN
int dy[] = {-1, 1, 0, 0};  // LEFT, RIGHT, UP, DOWN

int esMovimientoValido(Mapa mapa, Punto destino) {
    return destino.x >= 0 && destino.x < mapa->N &&
           destino.y >= 0 && destino.y < mapa->M &&
           mapa->mat[destino.x][destino.y] != '#'; // Asumiendo que 'X' indica un obstáculo
}

int moverRobot(Mapa mapa, Punto destino) {
    fprintf(stderr, "> MOVER: (%d, %d) -> (%d, %d)\n", mapa->robot.x, mapa->robot.y, destino.x, destino.y);
    int deltaX = destino.x - mapa->robot.x;
    int deltaY = destino.y - mapa->robot.y;

    Direccion dir;
    if (deltaX == 0 && deltaY < 0) {
        dir = LEFT;
    } else if (deltaX == 0 && deltaY > 0) {
        dir = RIGHT;
    } else if (deltaX < 0 && deltaY == 0) {
        dir = UP;
    } else if (deltaX > 0 && deltaY == 0) {
        dir = DOWN;
    } else {
        return 0; // Movimiento no válido
    }

    Punto nuevoPunto;
    nuevoPunto.x = mapa->robot.x + dx[dir];
    nuevoPunto.y = mapa->robot.y + dy[dir];

    if (esMovimientoValido(mapa, nuevoPunto)) {
        mapa->robot = nuevoPunto;
        return 1;
    } else {
        return 0; // Movimiento no válido
    }
}

int calcularCosto(Mapa mapa, Punto punto) {
    // Distancia Manhattan entre el punto actual y el objetivo
    int distanciaManhattan = abs(punto.x - mapa->objetivo.x) + abs(punto.y - mapa->objetivo.y);
    return distanciaManhattan;
}

void inmeddiate_planning(Mapa mapa) {
    usar_sensor(mapa);
    ColaP cola = mapa->cola;

    int** gScore = (int**)malloc(mapa->N * sizeof(int*));
    for (int i = 0; i < mapa->N; i++) {
        gScore[i] = (int*)malloc(mapa->M * sizeof(int));
        for (int j = 0; j < mapa->M; j++) {
            gScore[i][j] = INT_MAX;
        }
    }
    gScore[mapa->robot.x][mapa->robot.y] = 0;

    Punto inicio = mapa->robot;
    inicio.costo = calcularCosto(mapa, inicio);
    cola_insertar(cola, inicio);

    while (!cola_vacia(cola)) {
        Punto actual = cola_extraer_min(cola);

        if (actual.x == mapa->objetivo.x && actual.y == mapa->objetivo.y) {
            // printf("Objetivo alcanzado en (%d, %d)\n", actual.x, actual.y);
            return;
        }

        for (int dir = 0; dir < 4; dir++) {
            Punto vecino;
            vecino.x = actual.x + dx[dir];
            vecino.y = actual.y + dy[dir];

            if (!esMovimientoValido(mapa, vecino)) continue;

            int tentative_gScore = gScore[actual.x][actual.y] + 1;

            if (tentative_gScore < gScore[vecino.x][vecino.y]) {
                gScore[vecino.x][vecino.y] = tentative_gScore;
                vecino.costo = tentative_gScore + calcularCosto(mapa, vecino);
                cola_insertar(cola, vecino);

                moverRobot(mapa, vecino);
            }
        }
    }

    //printf("No se encontró un camino al objetivo.\n");

    for (int i = 0; i < mapa->N; i++) {
        free(gScore[i]);
    }
    free(gScore);
}


int main() {
  int N, M, D;
  scanf("%d%d%d", &N, &M, &D);
  int i1 , j1;
  scanf("%d%d", &i1, &j1);
  int i2 , j2;
  scanf("%d%d", &i2, &j2);

  Mapa mapa = mapa_crear(N, M, D, i1, j1, i2, j2);
  inmeddiate_planning(mapa);
  imprimir_mapa(mapa);
  destruir_mapa(mapa);

  return 0;
}