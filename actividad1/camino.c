#include "camino.h"
#include <stdlib.h>

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