#include "camino.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <archivo>\n", argv[0]);
    exit(1);
  }

  Info info = info_crear(argv[1]);
  if (!info) {
    printf("Archivo no encontrado o no válido\n");
    exit(2);
  }

  Mapa mapa = mapa_crear(info);
  Robot robot = robot_crear(info);
  destruir_info(info);

  imprimir_mapa(mapa);

  encontrar_camino(mapa, robot);
  
  destruir_mapa(mapa);
  destruir_robot(robot);

  return 0;
}