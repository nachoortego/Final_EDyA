#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>
#include "mapa.h"

/**
 * Imprime la dirección proporcionada.
 * 
 * @param dato Dirección a imprimir. Se espera un valor de tipo `Direccion`.
 */
__attribute__((unused)) static void imprimir_direccion(void *dato) {
  Direccion dir = (Direccion)(intptr_t)dato; // Cast explícito
  switch (dir) {
    case LEFT:
      fprintf(stderr, "L");
      break;
    case RIGHT:
      fprintf(stderr, "R");
      break;
    case UP:
      fprintf(stderr, "U");
      break;
    case DOWN:
      fprintf(stderr, "D");
      break;
  }
}

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
    fprintf(stderr, "SENSOR: %d %d %d %d\n", d1, d2, d3, d4);

    for(int i = 1; i < d1; i++)
      if((mapa->mat[mapa->robot.y - i][mapa->robot.x] != '_') && (mapa->mat[mapa->robot.y - i][mapa->robot.x] != 'F'))
        mapa->mat[mapa->robot.y - i][mapa->robot.x] = '.'; // Sensor hacia arriba

    for(int i = 1; i < d2; i++)
      if((mapa->mat[mapa->robot.y + i][mapa->robot.x] != '_') && (mapa->mat[mapa->robot.y + i][mapa->robot.x] != 'F'))
        mapa->mat[mapa->robot.y + i][mapa->robot.x] = '.'; // Sensor hacia abajo

    for(int i = 1; i < d3; i++)
      if((mapa->mat[mapa->robot.y][mapa->robot.x - i] != '_') && (mapa->mat[mapa->robot.y][mapa->robot.x - i] != 'F'))
        mapa->mat[mapa->robot.y][mapa->robot.x - i] = '.'; // Sensor hacia la izquierda

    for(int i = 1; i < d4; i++)
      if((mapa->mat[mapa->robot.y][mapa->robot.x + i] != '_') && (mapa->mat[mapa->robot.y][mapa->robot.x + i] != 'F'))
        mapa->mat[mapa->robot.y][mapa->robot.x + i] = '.'; // Sensor hacia la derecha

    tablahash_insertar(mapa->sensores, &mapa->robot); // Inserta el punto en la tabla de sensores
    imprimir_mapa(mapa);
    return 1;
  }
  return 0;
}

/**
 * Acerca al robot lo más posible al objetivo, evitando obstáculos y considerando celdas visitadas como obstáculos.
 * La dirección de movimiento se decide aleatoriamente, priorizando primero los movimientos horizontales o verticales.
 * 
 * @param mapa El mapa en el que el robot se mueve.
 */
static void camino_corto(Mapa mapa) {
  usar_sensor(mapa); // Usa el sensor para actualizar el mapa
  fprintf(stderr, "CAMINO CORTO\n");
  int moved = 1;
  int any_moved = 0;
  while (moved) {
    int priority = rand() % 2;
    moved = 0;
    int dx = mapa->objetivo.x - mapa->robot.x; // Distancia x al objetivo
    int dy = mapa->objetivo.y - mapa->robot.y; // Distancia y al objetivo

    // Prioriza movimientos segun la distancia al objetivo
    if(priority) { // Si priority es 1, el robot opta por movimientos horizontales
      if (dx > 0 && move(mapa, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, LEFT, 1))
        moved = 1;
      else if (dy > 0 && move(mapa, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, UP, 1))
        moved = 1;
    }
    else { // Si priority es 0, opta por movimientos verticales
      if (dy > 0 && move(mapa, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, UP, 1))
        moved = 1;
      else if (dx > 0 && move(mapa, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, LEFT, 1))
        moved = 1;
    }

    if(moved) 
      any_moved = 1;
  }
  if(any_moved){ // Si se movio, usa el sensor nuevamente
    fprintf(stderr, "SE MOVIO, USA SENSOR\n");
    if(usar_sensor(mapa)) // Usa el sensor para actualizar el mapa
      camino_corto(mapa); // Vuelve a buscar un camino corto
  }
}

/**
 * Comprueba si el robot ha llegado al objetivo.
 * 
 * @param mapa El mapa en el que el robot se encuentra.
 * @return 1 si el robot está en la posición del objetivo, 0 en caso contrario.
 */
static int check_estado(Mapa mapa) {
  return mapa->robot.x == mapa->objetivo.x && mapa->robot.y == mapa->objetivo.y;
}

/**
 * Funcion que no realiza ninguna acción, utilizada para la pila_desapilar.
 * 
 * @param dir Datos que se deben ignorar, ya que la función no realiza ninguna operación.
 */
static void no_destruir(void* dir) {}

/**
 * Imprime un caracter, utilizado para enviar el camino al sensor.
 * 
 * @param dato Puntero a un carácter que se desea imprimir.
 */
static void imprimir_char(void* dato) {
  char c = *(char*)dato;
  printf("%c", c);
}

/**
 * Busca celdas adyacentes no visitadas y mueve el robot hacia una de ellas.
 * La dirección de movimiento se decide aleatoriamente, priorizando primero los movimientos horizontales o verticales.
 * 
 * @param mapa El mapa en el que el robot se mueve.
 * @return 1 si se movió a una celda no visitada, 0 si no se encontraron celdas no visitadas.
 */
static int buscar_no_visitados(Mapa mapa) {
  fprintf(stderr, "NO VISITADOS\n");
  int priority = rand() % 2; // Elección aleatoria
  Direccion dirs[4];

  // Arreglo de direcciones posibles
  if (priority) {
    Direccion temp[] = { LEFT, RIGHT, UP, DOWN }; // Si priority es 1, el robot opta por movimientos horizontales
    for (int i = 0; i < 4; i++) {
      dirs[i] = temp[i];
    }
  } else {
    Direccion temp[] = { UP, DOWN, LEFT, RIGHT }; // Si priority es 0, opta por movimientos verticales
    for (int i = 0; i < 4; i++) {
      dirs[i] = temp[i];
    }
  }

  // Itera sobre cada dirección y verifica si hay celdas sin visitar
  for (int i = 0; i < 4; i++) {
    if (move(mapa, dirs[i], 1)) {
      return 1; // Celda sin visitar encontrada
    }
  }
  return 0; // No se encontraron celdas sin visitar
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

/**
 * Encuentra un camino al objetivo.
 * Al terminar, envía el camino al programa sensor para verificar.
 * 
 * @param mapa El mapa en el que el robot se mueve.
 */
void encontrar_camino(Mapa mapa) {
  if (check_estado(mapa)) { // Si el robot ya está en el objetivo
    printf("! \n");
    fflush(stdout);
  }
  srand(time(NULL)); // Semilla aleatoria
  while (!check_estado(mapa)) { // Mientras el robot no esté en el objetivo
    camino_corto(mapa); // Se acerca lo más posible al objetivo
    if (!check_estado(mapa)) {
      if (buscar_no_visitados(mapa)) {}  // Se mueve a casillas no visitadas
      else { // Si no las hay, vuelve en sus movimientos hasta que se pueda acercar nuevamente al objetivo
        fprintf(stderr, "RETROCEDER\n");
        Direccion retroceder = reverse((Direccion)(intptr_t)pila_tope(mapa->pila)); // Casteo explícito de void* a Direccion
        move(mapa, retroceder, 0); // Retrocede usando la pila, se pasa el valor 0 a 'move' para permitir volver a casillas visitadas
        mapa->pila = pila_desapilar(mapa->pila, no_destruir);
      }
    }
  }
  enviar_camino(mapa); // Envía el camino al sensor
}
