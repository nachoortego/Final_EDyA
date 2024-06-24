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
}_Mapa;

typedef _Mapa* Mapa;

Mapa leer_archivo (char filename[]) {
  FILE* archivo;
  archivo = fopen(filename, "r");
  if (archivo == NULL) {
    return NULL;  // Archivo no encontrado
  }


  Mapa mapa = malloc(sizeof(_Mapa));

  fscanf(archivo, "%d%d", &mapa->N, &mapa->M);
  fscanf(archivo, "%d%d", &mapa->a.x, &mapa->a.y);
  fscanf(archivo, "%d%d", &mapa->b.x, &mapa->b.y);

  mapa->mat = malloc(sizeof(char*)*mapa->N);
  for (int i = 0; i < mapa->M; i++)
    mapa->mat[i] = malloc(sizeof(char)*mapa->N);

  char line[LINE_SIZE];
  for (int i = 0; fgets(line, LINE_SIZE, archivo) != NULL; i++){
    strcpy(mapa->mat[i], line);
  }

  fclose(archivo);

  return mapa;
}

void imprimir_mapa(Mapa mapa) {
  for (int i = 0; i < mapa->M; i++){
    for (int j = 0; j < mapa->N; j++)
      printf("%c ",mapa->mat[i][j]);
    printf("\n");
  }
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <archivo>\n", argv[0]);
    exit(1);
  }
  Mapa mapa = leer_archivo(argv[1]);
  if(!mapa){
    printf("Archivo no encontrado\n");
    exit(2);
  }

  imprimir_mapa(mapa);

  return 0;
}