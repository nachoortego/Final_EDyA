#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 255

typedef struct {
  int x;
  int y;
} Punto;

typedef struct {
  char** mat;
  int M;
  int N;
  Punto a;
  Punto b;
} _Mapa;

typedef _Mapa* Mapa;


int verificar_archivo(FILE* archivo, Mapa mapa) {
  if (fscanf(archivo, "%d%d", &mapa->N, &mapa->M) != 2 || mapa->N <= 0 || mapa->M <= 0)
    return 0; // fscanf guarda 2 valores y valores mayores a cero

  if (fscanf(archivo, "%d%d", &mapa->a.x, &mapa->a.y) != 2 ||
      mapa->a.x < 0 || mapa->a.x >= mapa->N || mapa->a.y < 0 || mapa->a.y >= mapa->M)
    return 0; // fscanf guarda 2 valores y valores mayores a cero y en el rango

  if (fscanf(archivo, "%d%d", &mapa->b.x, &mapa->b.y) != 2 ||
      mapa->b.x < 0 || mapa->b.x >= mapa->N || mapa->b.y < 0 || mapa->b.y >= mapa->M)
    return 0; // fscanf guarda 2 valores y valores mayores a cero y en el rango

  // Leer una línea en blanco
  char line[LINE_SIZE];
  if (fgets(line, LINE_SIZE, archivo) == NULL)
    return 0;

  // Verificar dimensiones del mapa y caractres del mapa
  for (int i = 0; i < mapa->N; i++) {
    if (fgets(line, LINE_SIZE, archivo) == NULL || strlen(line) < mapa->M) 
      return 0; 

    for(int j = 0; j < mapa->M; j++)
      if(line[j] != '#' && line[j] != '.') {
        printf("XD");
        return 0;
      }
  }

  // Resetear el archivo para leerlo nuevamente
  fseek(archivo, 0, SEEK_SET);
  return 1;
}

Mapa leer_archivo(char filename[]) {
  FILE* archivo = fopen(filename, "r");
  if (archivo == NULL) 
    return NULL; // Archivo no encontrado

  Mapa mapa = malloc(sizeof(_Mapa));
  if(!verificar_archivo(archivo, mapa)) {
    fclose(archivo);
    return NULL; // Archivo no válido
  }

  fscanf(archivo, "%d%d", &mapa->N, &mapa->M);
  fscanf(archivo, "%d%d", &mapa->a.x, &mapa->a.y);
  fscanf(archivo, "%d%d", &mapa->b.x, &mapa->b.y);

  // Inicializar matriz
  mapa->mat = malloc(sizeof(char*) * mapa->N);
  for (int i = 0; i < mapa->N; i++) {
    mapa->mat[i] = malloc(sizeof(char) * (mapa->M + 1)); // +1 para el '\0'
  }

  // Leer líneas del archivo
  char line[LINE_SIZE];
  fgets(line, LINE_SIZE, archivo); // Omitir la línea en blanco
  for (int i = 0; i < mapa->N; i++) {
    fgets(line, LINE_SIZE, archivo);
    strncpy(mapa->mat[i], line, mapa->M);
    mapa->mat[i][mapa->M] = '\0'; // Asegurar la terminación de la cadena
  }

  fclose(archivo);
  return mapa;
}

void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    for (int j = 0; j < mapa->M; j++)
      printf("%c ", mapa->mat[i][j]);
    printf("\n");
  }
}

void liberar_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->N; i++) {
    free(mapa->mat[i]);
  }
  free(mapa->mat);
  free(mapa);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <archivo>\n", argv[0]);
    exit(1);
  }

  Mapa mapa = leer_archivo(argv[1]);
  if (!mapa) {
    printf("Archivo no encontrado\n");
    exit(2);
  }

  imprimir_mapa(mapa);
  liberar_mapa(mapa);

  return 0;
}