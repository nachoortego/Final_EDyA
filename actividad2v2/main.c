#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "mapa.h"

#define INT_MAX 99 //2147483647

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

    if((mapa->robot.y - d1) >= 0)
      mapa->mat[mapa->robot.y - d1][mapa->robot.x] = '#'; // Marca la casilla final

    for(int i = 1; i < d2; i++)
      if(mapa->mat[mapa->robot.y + i][mapa->robot.x] != 'F')
        mapa->mat[mapa->robot.y + i][mapa->robot.x] = '.'; // Sensor hacia abajo

    if((mapa->robot.y + d2) < mapa->N)
      mapa->mat[mapa->robot.y + d2][mapa->robot.x] = '#'; // Marca la casilla final

    for(int i = 1; i < d3; i++)
      if(mapa->mat[mapa->robot.y][mapa->robot.x - i] != 'F')
        mapa->mat[mapa->robot.y][mapa->robot.x - i] = '.'; // Sensor hacia la izquierda

    if((mapa->robot.x - d3) >= 0)
      mapa->mat[mapa->robot.y][mapa->robot.x - d3] = '#'; // Marca la casilla final

    for(int i = 1; i < d4; i++)
      if(mapa->mat[mapa->robot.y][mapa->robot.x + i] != 'F')
        mapa->mat[mapa->robot.y][mapa->robot.x + i] = '.'; // Sensor hacia la derecha
    
    if((mapa->robot.x + d4) < mapa->M)
      mapa->mat[mapa->robot.y][mapa->robot.x + d4] = '#'; // Marca la casilla final

    tablahash_insertar(mapa->sensores, &mapa->robot); // Inserta el punto en la tabla de sensores
    imprimir_mapa(mapa);
    return 1;
  }
  return 0;
}

static void imprimir_char(void* dato) {
  char c = *(char*)dato;
  printf("%c", c);
}

/**
 * Envía el camino recorrido al sensor.
 * 
 * @param mapa El mapa que contiene el camino que se desea enviar.
 */
static void enviar_camino(Mapa mapa) {
  printf("! ");
  arreglo_recorrer(mapa->camino, imprimir_char);
  printf("\n");
  fflush(stdout);
}

// Arrays para mapeo de movimientos
int dx[] = {0, 0, -1, 1};  // LEFT, RIGHT, UP, DOWN
int dy[] = {-1, 1, 0, 0};  // LEFT, RIGHT, UP, DOWN

int calcularCosto(Mapa mapa, Punto punto) {
  // Distancia Manhattan entre el punto actual y el objetivo
  int distanciaManhattan = abs(punto.x - mapa->objetivo.x) + abs(punto.y - mapa->objetivo.y);
  return distanciaManhattan;
}

void generar_g_score_optimista(Mapa mapa, int** gScore) {
  // Inicializa gScore con un valor alto (infinito)
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      gScore[i][j] = INT_MAX;
    }
  }

  // El gScore del objetivo es 0, ya que es el punto de partida para el cálculo
  Punto objetivo = mapa->objetivo;
  gScore[objetivo.y][objetivo.x] = 0;

  // Cola de prioridad para explorar los puntos desde el objetivo
  ColaP cola = cola_crear(1000);
  cola_insertar(cola, objetivo);

  while (!cola_vacia(cola)) {
    Punto actual = cola_extraer_min(cola);

    for (int dir = 0; dir < 4; dir++) {
      Punto vecino;
      vecino.x = actual.x + dx[dir];
      vecino.y = actual.y + dy[dir];

      // Verificar que el vecino esté dentro del mapa
      if (vecino.x < 0 || vecino.x >= mapa->M || vecino.y < 0 || vecino.y >= mapa->N) continue;

      // Evitar recalcular para celdas con obstáculos conocidos
      if (mapa->mat[vecino.y][vecino.x] == '#') continue;

      int tentative_gScore = gScore[actual.y][actual.x] + 1;

      if (tentative_gScore < gScore[vecino.y][vecino.x]) {
        gScore[vecino.y][vecino.x] = tentative_gScore;
        vecino.costo = tentative_gScore;
        cola_insertar(cola, vecino);
      }
    }
  }

  cola_destruir(cola);  // Destruir la cola después de usarla
}

static void mostrar_g_score(Mapa mapa, int** gScore) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      fprintf(stderr, "%d ", gScore[i][j]);
    }
    fprintf(stderr, "\n");
  }
}


int main() {
  int N, M, D;
  scanf("%d%d%d", &N, &M, &D);
  int i1 , j1;
  scanf("%d%d", &i1, &j1);
  int i2 , j2;
  scanf("%d%d", &i2, &j2);

  Mapa mapa = mapa_crear(N, M, D, i1, j1, i2, j2);
  // inmeddiate_planning(mapa);

  // Ejemplo de cómo usarlo en tu algoritmo principal:
  int** gScore = (int**)malloc(mapa->N * sizeof(int*));
  for (int i = 0; i < mapa->N; i++) {
      gScore[i] = (int*)malloc(mapa->M * sizeof(int));
  }

  generar_g_score_optimista(mapa, gScore);

  mostrar_g_score(mapa, gScore);

  usar_sensor(mapa);

  generar_g_score_optimista(mapa, gScore);

  mostrar_g_score(mapa, gScore);


  for (int i = 0; i < mapa->N; i++) {
      free(gScore[i]);
  }
  free(gScore);

  imprimir_mapa(mapa);
  enviar_camino(mapa);
  destruir_mapa(mapa);

  return 0;
}