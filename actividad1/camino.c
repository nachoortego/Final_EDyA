#include "camino.h"
#include <stdlib.h>
#include <stdint.h>

/**
 * Funcion local que toma pila_apilar como argumento. 
 * No devuelve una copia fisica.
 */
static void* no_copiar(void* dato) {
  return dato; // Devuelve el mismo dato sin realizar una copia
}

int move(Mapa mapa, Robot robot, Direccion dir, int ignorarRepetidos) {
  switch (dir) {
    case LEFT:
      Punto nuevoPunto = crear_punto(robot->pos.x - 1, robot->pos.y);
      if ((robot->pos.x - 1) >= 0 &&
          mapa->mat[robot->pos.y][robot->pos.x - 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || tablahash_buscar(robot->visitados, &nuevoPunto))) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        
        mapa->mat[robot->pos.y][robot->pos.x] = '_'; // Marca la casilla como visitada
        /*! BORRAR: Marcar casilla como '_' */

        tabla_hash_insertar(robot->visitados, &(robot->pos)); // Inserta la casilla en la tabla de visitados
        robot->pos.x--; 
        mapa->mat[robot->pos.y][robot->pos.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          robot->camino = pila_apilar(robot->camino, (void*)LEFT, no_copiar); // Apila el movimiento realizado
        printf("L\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case RIGHT:
      Punto nuevoPunto = crear_punto(robot->pos.x + 1, robot->pos.y);
      if ((robot->pos.x + 1) < mapa->M &&
          mapa->mat[robot->pos.y][robot->pos.x + 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || tablahash_buscar(robot->visitados, &nuevoPunto))) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        
        mapa->mat[robot->pos.y][robot->pos.x] = '_'; // Marca la casilla como visitada
        /*! BORRAR: Marcar casilla como '_' */

        tabla_hash_insertar(robot->visitados, &(robot->pos)); // Inserta la casilla en la tabla de visitados
        robot->pos.x++; 
        mapa->mat[robot->pos.y][robot->pos.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          robot->camino = pila_apilar(robot->camino, (void*)RIGHT, no_copiar ); // Apila el movimiento realizado
        printf("R\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case UP:
      Punto nuevoPunto = crear_punto(robot->pos.x, robot->pos.y - 1);
      if ((robot->pos.y - 1) >= 0 &&
          mapa->mat[robot->pos.y - 1][robot->pos.x] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || tablahash_buscar(robot->visitados, &nuevoPunto))) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        
        mapa->mat[robot->pos.y][robot->pos.x] = '_'; // Marca la casilla como visitada
        /*! BORRAR: Marcar casilla como '_' */

        tabla_hash_insertar(robot->visitados, &(robot->pos)); // Inserta la casilla en la tabla de visitados
        robot->pos.y--; 
        mapa->mat[robot->pos.y][robot->pos.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          robot->camino = pila_apilar(robot->camino, (void*)UP, no_copiar); // Apila el movimiento realizado
        printf("U\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case DOWN:
      Punto nuevoPunto = crear_punto(robot->pos.x, robot->pos.y + 1);
      if ((robot->pos.y + 1) < mapa->N &&
          mapa->mat[robot->pos.y + 1][robot->pos.x] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || tablahash_buscar(robot->visitados, &nuevoPunto))) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        
        mapa->mat[robot->pos.y][robot->pos.x] = '_'; // Marca la casilla como visitada
        /*! BORRAR: Marcar casilla como '_' */

        tabla_hash_insertar(robot->visitados, &(robot->pos)); // Inserta la casilla en la tabla de visitados
        robot->pos.y++; 
        mapa->mat[robot->pos.y][robot->pos.x] = 'R'; // Mueve el robot
        if(ignorarRepetidos) // Si no estoy haciendo backtracking, apilo
          robot->camino = pila_apilar(robot->camino, (void*)DOWN, no_copiar); // Apila el movimiento realizado
        printf("D\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;
  }
  return 0; // En caso de no haberse movido
}

static void camino_corto(Mapa mapa, Robot robot) {
  srand(time(NULL));
  int moved = 1;
  while (moved) {
    int priority = rand() % 2;
    moved = 0;
    int dx = robot->obj.x - robot->pos.x; // Distancia x al objetivo
    int dy = robot->obj.y - robot->pos.y; // Distancia y al objetivo

    // Prioriza movimientos segun la distancia al objetivo
    if(priority) { // Si priority es 1, el robot opta por movimientos horizontales
      if (dx > 0 && move(mapa, robot, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, robot, LEFT, 1))
        moved = 1;
      else if (dy > 0 && move(mapa, robot, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, robot, UP, 1))
        moved = 1;
    }
    else { // Si priority es 0, opta por movimientos verticales
      if (dy > 0 && move(mapa, robot, DOWN, 1))
        moved = 1;
      else if (dy < 0 && move(mapa, robot, UP, 1))
        moved = 1;
      else if (dx > 0 && move(mapa, robot, RIGHT, 1))
        moved = 1;
      else if (dx < 0 && move(mapa, robot, LEFT, 1))
        moved = 1;
    }
  }
}

static int check_estado(Robot robot) {
  return robot->pos.x == robot->obj.x && robot->pos.y == robot->obj.y;
}

/**
 * Funcion que se pasa como parámetro a pila_desapilar, no destruye el dato.
 */
static void no_destruir(void* dir) {}

static int buscar_no_visitados(Mapa mapa, Robot robot) {
  int priority = rand() % 2; // Eleccion aleatoria
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
    if (move(mapa, robot, dirs[i], 1)) {
      return 1; // Celda sin visitar encontrada
    }
  }
  return 0; // No se encontraron celdas sin visitar
}

/**
 * Dado un mapa valido, encuentra un camino al objetivo e imprime cada movimiento del robot.
 */
void encontrar_camino(Mapa mapa, Robot robot) {
  if(check_estado(robot)) // Si el robot ya esta en el objetivo
    printf("Completado!\n");
  while(!check_estado(robot)) { // Mientras el robot no este en el objetivo
    camino_corto(mapa, robot); // Se acerca lo mas posible al objetivo
    if(!check_estado(mapa)) {
      if(buscar_no_visitados(mapa, robot)) {} // Se mueve a casillas no visitadas
      else { // Si no las hay, vuelve en sus movimientos hasta que se pueda acercar nuevamente al objetivo
        Direccion retroceder = reverse((Direccion)(intptr_t) pila_tope(robot->camino)); // Casteo explicito de void* a Direccion
        move(mapa, robot, retroceder, 0); // Retrocede usando la pila, se pasa el valor 0 a 'move' para permitir volver a casillas visitadas
        robot->camino = pila_desapilar(robot->camino, no_destruir);
      }
    }
  }
  pila_recorrer(robot->camino, imprimir_direccion);
  printf("\nCompletado!\n");
}