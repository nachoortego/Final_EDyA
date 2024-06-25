#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <archivo>\n", argv[0]);
    exit(1);
  }

  Mapa mapa = mapa_crear(argv[1]);
  if (!mapa) {
    printf("Archivo no encontrado o no válido\n");
    exit(2);
  }

  imprimir_mapa(mapa);
  destruir_mapa(mapa);

  return 0;
}