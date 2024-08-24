#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "mapa.h"

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

int main() {
  int N, M, D;
  scanf("%d%d%d", &N, &M, &D);
  int i1 , j1;
  scanf("%d%d", &i1, &j1);
  int i2 , j2;
  scanf("%d%d", &i2, &j2);

  Mapa mapa = mapa_crear(N, M, D, i1, j1, i2, j2);
  usar_sensor(mapa);
  destruir_mapa(mapa);

  return 0;
}