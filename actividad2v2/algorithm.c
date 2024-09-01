#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <limits.h>
#include "mapa.h"

int lanzar_rayos(Mapa mapa, Punto origen, int d1, int d2, int d3, int d4) {
  int muro_detectado = 0;

  for(int i = 1; i < d1; i++){
    if(mapa->mat[mapa->robot.y - i][mapa->robot.x] != 'F')
      mapa->mat[mapa->robot.y - i][mapa->robot.x] = '_'; // Sensor hacia arriba
  }

  if(d1 <= mapa->D && (mapa->robot.y - d1) >= 0) {
    mapa->mat[mapa->robot.y - d1][mapa->robot.x] = '#'; // Marca la casilla final
    muro_detectado = 1;
  }

  for(int i = 1; i < d2; i++)
    if(mapa->mat[mapa->robot.y + i][mapa->robot.x] != 'F')
      mapa->mat[mapa->robot.y + i][mapa->robot.x] = '_'; // Sensor hacia abajo

  if(d2 <= mapa->D && (mapa->robot.y + d2) < mapa->N) {
    mapa->mat[mapa->robot.y + d2][mapa->robot.x] = '#'; // Marca la casilla final
    muro_detectado = 1;
  }

  for(int i = 1; i < d3; i++)
    if(mapa->mat[mapa->robot.y][mapa->robot.x - i] != 'F')
      mapa->mat[mapa->robot.y][mapa->robot.x - i] = '_'; // Sensor hacia la izquierda

  if(d3 <= mapa->D && (mapa->robot.x - d3) >= 0) {
    mapa->mat[mapa->robot.y][mapa->robot.x - d3] = '#'; // Marca la casilla final
    muro_detectado = 1;
  }

  for(int i = 1; i < d4; i++)
    if(mapa->mat[mapa->robot.y][mapa->robot.x + i] != 'F')
      mapa->mat[mapa->robot.y][mapa->robot.x + i] = '_'; // Sensor hacia la derecha
  
  if(d4 <= mapa->D && (mapa->robot.x + d4) < mapa->M) {
    mapa->mat[mapa->robot.y][mapa->robot.x + d4] = '#'; // Marca la casilla final
    muro_detectado = 1;
  }

  return muro_detectado;
}

int max_rayos(int d1, int d2, int d3, int d4, int d_max){
  int max = --d1;

  if(--d2 > max)
    max = d2;
  if(--d3 > max)
    max = d3;
  if(--d4 > max)
    max = d4;

  return max > d_max ? max : d_max;
}

int usar_sensor(Mapa mapa) {
  int d1, d2, d3, d4;
  int muro_detectado = 0;

  printf("? %d %d\n", mapa->robot.y, mapa->robot.x);
  fflush(stdout);
  scanf("%d%d%d%d", &d1, &d2, &d3, &d4);

  mapa->D = max_rayos(d1, d2, d3, d4, mapa->D);

  muro_detectado = lanzar_rayos(mapa, mapa->robot, d1, d2, d3, d4);

  imprimir_mapa(mapa);

  return muro_detectado;
}

static void imprimir_char(void* dato) {
  char c = *(char*)dato;
  printf("%c", c);
}

void enviar_camino(Mapa mapa) {
  printf("! ");
  arreglo_recorrer(mapa->camino, imprimir_char);
  printf("\n");
  fflush(stdout);
}

void generar_g_score(Mapa mapa) {
  // Inicializa gScore con un valor alto (infinito)

  for (int i = 0; i < mapa->N; i++) 
    for (int j = 0; j < mapa->M; j++) 
      mapa->gScore[i][j] = INT_MAX;

  // El gScore del objetivo es 0, ya que es el punto de partida para el cálculo
  Punto objetivo = mapa->objetivo;
  mapa->gScore[objetivo.y][objetivo.x] = 0;

  // Cola de prioridad para explorar los puntos desde el objetivo
  Cola cola = cola_crear(mapa->N * mapa->M);
  cola_insertar(cola, objetivo);

  while (!cola_vacia(cola)) {
    Punto actual = cola_extraer(cola);

    // Si ya hemos alcanzado la posición del robot, podemos detenernos
    if (actual.x == mapa->robot.x && actual.y == mapa->robot.y)
      break; // Detenemos el algoritmo ya que encontramos el camino al robot

    for (int dir = 0; dir < 4; dir++) {
      Punto vecino;
      // Arrays para mapeo de movimientos
      int dx[] = {0, 0, -1, 1};  // LEFT, RIGHT, UP, DOWN
      int dy[] = {-1, 1, 0, 0};  // LEFT, RIGHT, UP, DOWN
      vecino.x = actual.x + dx[dir];
      vecino.y = actual.y + dy[dir];

      if (movimiento_valido(mapa, vecino)) {
        int tentative_gScore = mapa->gScore[actual.y][actual.x] + 1;

        if (tentative_gScore < mapa->gScore[vecino.y][vecino.x]) {
          mapa->gScore[vecino.y][vecino.x] = tentative_gScore;
          cola_insertar(cola, vecino);
        }
      }
    }
  }

  cola_destruir(cola);  // Destruir la cola después de usarla
}

static void mostrar_g_score(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      fprintf(stderr, "%d ", mapa->gScore[i][j]);
    }
    fprintf(stderr, "\n");
  }
}

static int vecino_desconocido(Mapa mapa, Punto vecino) {
  return !(mapa->mat[vecino.y][vecino.x] == '_' || mapa->mat[vecino.y][vecino.x] == 'F');
}

static int robot_ha_llegado(Mapa mapa) {
  return mapa->robot.x == mapa->objetivo.x && mapa->robot.y == mapa->objetivo.y;
}

void path_finding(Mapa mapa) {
  usar_sensor(mapa);
  generar_g_score(mapa);
  mostrar_g_score(mapa);

  while (!robot_ha_llegado(mapa)) {
    Punto mejor_vecino;
    int mejor_gScore = INT_MAX;
    int movimiento_posible = 0;
    int muro_detectado = 0;

    for (int dir = 0; dir < 4; dir++) {
      Punto vecino;
      
      // Arrays para mapeo de movimientos
      int dx[] = {0, 0, -1, 1};  // LEFT, RIGHT, UP, DOWN
      int dy[] = {-1, 1, 0, 0};  // LEFT, RIGHT, UP, DOWN

      vecino.x = mapa->robot.x + dx[dir];
      vecino.y = mapa->robot.y + dy[dir];

      if (movimiento_valido(mapa, vecino)) {
        int gScore_vecino = mapa->gScore[vecino.y][vecino.x];

        if (gScore_vecino <= mejor_gScore) {
          if (gScore_vecino < mejor_gScore || (mapa->mat[vecino.y][vecino.x] == '_')) {
            mejor_gScore = gScore_vecino;
            mejor_vecino = vecino;
            movimiento_posible = 1;
          }
        }
      }
    }

    if (movimiento_posible) {
      if (vecino_desconocido(mapa, mejor_vecino)) {
        muro_detectado = usar_sensor(mapa);
        if(muro_detectado)
          generar_g_score(mapa);
        if (movimiento_valido(mapa, mejor_vecino))
          mover_robot(mapa, mejor_vecino);
      }
      else
        mover_robot(mapa, mejor_vecino);
      }
  }
}