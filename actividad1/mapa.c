#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

/**
 * Toma como argumento el nombre de un archivo.
 * Devuelve un mapa con la informacion del archivo.
 * Devuelve NULL si el archivo no existe o no es válido.
 */
Mapa mapa_crear(char filename[]) {
  FILE* archivo = fopen(filename, "r");
  if (archivo == NULL) 
    return NULL; // Archivo no encontrado

  Mapa mapa = malloc(sizeof(_Mapa));
  assert(mapa != NULL);

  // Leer dimensiones y puntos a y b (primero y, luego x) , tambien verificar lectura y validez de los datos
  if (fscanf(archivo, "%d%d", &mapa->N, &mapa->M) != 2 || mapa->N <= 0 || mapa->M <= 0) {
    free(mapa);
    fclose(archivo);
    return NULL;
  }
  if (fscanf(archivo, "%d%d", &mapa->robot.y, &mapa->robot.x) != 2 ||
      mapa->robot.x < 0 || mapa->robot.x >= mapa->M || mapa->robot.y < 0 || mapa->robot.y >= mapa->N) {
    free(mapa);
    fclose(archivo);
    return NULL;
  }
  if (fscanf(archivo, "%d%d", &mapa->objetivo.y, &mapa->objetivo.x) != 2 ||
      mapa->objetivo.x < 0 || mapa->objetivo.x >= mapa->M || mapa->objetivo.y < 0 || mapa->objetivo.y >= mapa->N) {
    free(mapa);
    fclose(archivo);
    return NULL;   
  }

  // Leer linea en blanco
  char line[LINE_SIZE];
  if (fgets(line, LINE_SIZE, archivo) == NULL) {
    free(mapa);
    fclose(archivo);
    return NULL;
  }

  // Inicializar matriz
  mapa->mat = malloc(sizeof(char*) * mapa->N);
  assert(mapa->mat != NULL);
  for (int i = 0; i < mapa->N; i++) {
    mapa->mat[i] = malloc(sizeof(char) * (mapa->M + 1)); // +1 para el '\0'
    assert(mapa->mat[i] != NULL);
  }

  // Verificar dimensiones del mapa y caracteres del mapa
  for (int i = 0; i < mapa->N; i++) {
    if (fgets(line, LINE_SIZE, archivo) == NULL || strlen(line) < mapa->M) {
      destruir_mapa(mapa);
      fclose(archivo);
      return NULL; 
    }

    for (int j = 0; j < mapa->M; j++)
      if (line[j] != '#' && line[j] != '.') {
        destruir_mapa(mapa);
        fclose(archivo);
        return NULL;
      }

    strncpy(mapa->mat[i], line, mapa->M); // Copiar los datos
    mapa->mat[i][mapa->M] = '\0'; // Asegurar la terminación de la cadena
  }
  mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Escribir el robot en la matriz
  mapa->mat[mapa->objetivo.y][mapa->objetivo.x] = 'F'; // Escribir el objetivo en la matriz

  fclose(archivo);
  return mapa;
}

/**
 * Imprime el mapa por la salida estándar.
 */
void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++) {
      if (mapa->mat[i][j] == '#') {
        printf("\033[0;35m"); // Violeta para obstáculo
      } 
      else if (mapa->mat[i][j] == 'F') {
        printf("\033[0;32m"); // Verde para posición final
      } else {
        printf("\033[0;31m"); // Default rojo para cualquier otro caso
      }
      printf("%c ", mapa->mat[i][j]);
    }
  printf("\n");
  }
  printf("\033[0;37m\n"); // Restaura el color a blanco después del mapa
  getchar(); // Espera a que se presione Enter antes de continuar
}
// void imprimir_mapa(Mapa mapa) {
//   printf("\033[0;35m"); // violeta
//   for (int i = 0; i < mapa->N; i++) {
//     for (int j = 0; j < mapa->M; j++) {
//       mapa->mat[i][j] == '_' ? printf("\033[0;36m") : printf("\033[0;35m"); // cyan o violeta
//       mapa->mat[i][j] == '#' ? printf("\033[0;31m") : printf("\033[0;35m"); // rojo o violeta
//       mapa->mat[i][j] == 'R' ? printf("\033[0;34m") : printf("\033[0;35m"); // azul o violeta
//       mapa->mat[i][j] == 'F' ? printf("\033[0;32m") : printf("\033[0;35m"); // verde o violeta
//       printf("%c ", mapa->mat[i][j]);
//       printf("\033[0;35m");
//     }
//     printf("\n");
//   }
//   printf("\033[0;37m\n");
//   getchar();
// }

/**
 * Destruye el mapa y sus datos.
 */
void destruir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) { // Libera cada fila
    free(mapa->mat[i]);
  }
  free(mapa->mat); // Libera la matriz
  free(mapa);
}

/**
 * Funcion local que toma pila_apilar como argumento. 
 * No devuelve una copia fisica.
 */
static void* no_copiar(void* dato) {
  return dato; // Devuelve el mismo dato sin realizar una copia
}

/**
 * Mueve el robot hacia la direccion indicada si es posible e imprime su caracter correspondiente.
 * Cada movimiento es agregado a la pila del mapa.
 * El tercer parámetro es ignorarRepetidos. 
 * En caso de que ignorarRepetidos sea 1, las casillas validas se consideran obstaculos.
 * En caso de quue ignorarRepetidos sea 0, las casillas visitadas se consideran validas.
 * Devuelve 1 si fue posible el movimiento, 0 si no fue posible
 */
int move(Mapa mapa, Direccion dir, int ignorarRepetidos) {
  switch (dir) {
    case LEFT:
      if ((mapa->robot.x - 1) >= 0 &&
          mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y][mapa->robot.x - 1] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.x--; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        mapa->camino = pila_apilar(mapa->camino, (void*)LEFT, no_copiar); // Apila el movimiento realizado
        printf("L\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case RIGHT:
      if ((mapa->robot.x + 1) < mapa->M &&
          mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y][mapa->robot.x + 1] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.x++; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        mapa->camino = pila_apilar(mapa->camino, (void*)RIGHT, no_copiar ); // Apila el movimiento realizado
        printf("R\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case UP:
      if ((mapa->robot.y - 1) >= 0 &&
          mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y - 1][mapa->robot.x] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.y--; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        mapa->camino = pila_apilar(mapa->camino, (void*)UP, no_copiar); // Apila el movimiento realizado
        printf("U\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;

    case DOWN:
      if ((mapa->robot.y + 1) < mapa->N &&
          mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '#' && // Comprueba limites del mapa y obstaculos
          (ignorarRepetidos == 0 || mapa->mat[mapa->robot.y + 1][mapa->robot.x] != '_')) { // Si ignorarRepetidos es 1, no importa si la casilla fue visitada
        mapa->mat[mapa->robot.y][mapa->robot.x] = '_'; // Marca la casilla como visitada
        mapa->robot.y++; 
        mapa->mat[mapa->robot.y][mapa->robot.x] = 'R'; // Mueve el robot
        mapa->camino = pila_apilar(mapa->camino, (void*)DOWN, no_copiar); // Apila el movimiento realizado
        printf("D\n");
        imprimir_mapa(mapa);
        return 1;
      }
      break;
  }
  return 0; // En caso de no haberse movido
}

/**
 * Toma una direccion y devuelve su opuesta, utilizado para backtracking
 */
Direccion reverse(Direccion dir) {
  switch (dir) {
  case LEFT:
    return RIGHT;
  case RIGHT:
    return LEFT;
  case UP:
    return DOWN;
  case DOWN:
    return UP;
  default:
    return dir; // Devuelve por defecto, este caso no ocurre si dir esta bien definido
  }
}
