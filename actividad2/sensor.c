#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// leer_archivo()
// - lee el archivo `data` segun el formato especificado en el trabajo.
// - n, m, max_d, i1, j1, i2 y j2 son parametros de salida. Se corresponden con
//   los valores N, M, D, i1, j1, i2 y j2, respectivamente.
// - Devuelve un arreglo de arreglos con las filas del entorno, o NULL en caso
//   de que el formato sea invalido
char** leer_archivo(FILE* data, int* n, int* m, int* max_d, int* i1, int* j1, int* i2, int* j2) {
  *n = 0;  // Inicializa N 
  *m = 0;  // Inicializa M
  *max_d = 0;  // Inicializa max_d

  // Analizar los valores de la primera línea 
  if (fscanf(data, "%d%d%d", n, m, max_d) != 3 || *n <= 0 || *m <= 0 || *max_d <= 0) {
		printf("%d %d %d\n",  *n, *m, *max_d);
    return NULL;}

  // Segunda linea
  if (fscanf(data, "%d%d", i1, j1) != 2 ||
      *j1 < 0 || *j1 >= *m || *i1 < 0 || *i1 >= *n)
    return NULL;

  // Tercera linea
  if (fscanf(data, "%d%d", i2, j2) != 2 ||
      *j2 < 0 || *j2 >= *m || *i2 < 0 || *i2 >= *n)
    return NULL;   


  // Leer linea en blanco
  char line[255];
  if (fgets(line, 255, data) == NULL)
    return NULL;

  // Inicializar matriz
  char** mapa = malloc(sizeof(char*) * *n);
  for (int i = 0; i < *n; i++)
    mapa[i] = malloc(sizeof(char) * (*m + 1)); // +1 para el '\0'

  // Verificar dimensiones del mapa y caracteres del mapa
  for (int i = 0; i < *n; i++) {
    if (fgets(line, 255, data) == NULL || strlen(line) < *m) {
      free(mapa);
      return NULL; 
    }

    for (int j = 0; j < *m; j++)
      if (line[j] != '#' && line[j] != '.') {
        free(mapa);
        return NULL;
      }

    strncpy(mapa[i], line, *m); // Copiar los datos
    mapa[i][*m] = '\0'; // Asegurar la terminación de la cadena
  }
  mapa[*i1][*j1] = 'R'; // Escribir el robot en la matriz
  mapa[*i2][*j2] = 'F'; // Escribir el objetivo en la matriz

  return mapa;
}

// El resto de este archivo no tiene relevancia para el estudiante.

int coordenada_valida(int n, int m, int i, int j) {
	return 0 <= i && i < n && 0 <= j && j < m;
}

int lanzar_rayo(char** mapa, int n, int m, int i, int j, int di, int dj, int max_dist) {
	int dist = 0;
	while (coordenada_valida(n, m, i, j) && mapa[i][j] != '#') {
		dist++;
		i += di; j += dj;
	}
	return dist > max_dist ? max_dist+1 : dist;
}

int correr_sensor(char** mapa, int n, int m, int i, int j, int* d, int max_d) {
	if (!coordenada_valida(n, m, i, j)) return 0;
	d[0] = lanzar_rayo(mapa, n, m, i, j, -1, 0, max_d); // arriba
	d[1] = lanzar_rayo(mapa, n, m, i, j,  1, 0, max_d); // abajo
	d[2] = lanzar_rayo(mapa, n, m, i, j, 0, -1, max_d); // izquierda
	d[3] = lanzar_rayo(mapa, n, m, i, j, 0,  1, max_d); // derecha
	return 1;
}

void caracter_inesperado(char c) {
	fprintf(stderr, "Comando invalido. Caracter inesperado: '%c' (ascii %d)\n", c, (int)c); fflush(stderr);
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Uso: ./sensor <archivo>\n"); fflush(stderr);
		return EXIT_FAILURE;
	}

	FILE* data = fopen(argv[1], "r");
	if (!data) {
		fprintf(stderr, "No existe el archivo\n"); fflush(stderr);
		return EXIT_FAILURE;
	}

	int n, m, max_d;
	int i1, j1;
	int i2, j2;
	char** mapa;
	if ((mapa = leer_archivo(data, &n, &m, &max_d, &i1, &j1, &i2, &j2)) == NULL) {
		fprintf(stderr, "Formato de archivo invalido\n");
		fclose(data);
		return EXIT_FAILURE;
	}
	fclose(data);

	printf("%d %d %d\n", n, m, max_d);
	printf("%d %d\n", i1, j1);
	printf("%d %d\n", i2, j2);
	fflush(stdout);

	int operaciones = 0;

	while (1) {
		char c = getchar();

		if (isspace(c)) continue;
		else if (c == '?') {

			c = getchar();
			if (c != ' ') caracter_inesperado(c);

			int i, j;
			if (scanf("%d%d", &i, &j) != 2) caracter_inesperado(c);

			operaciones++;
			int d[4] = {};
			correr_sensor(mapa, n, m, i, j, d, max_d);

			for (int i = 0; i < 4; ++i) {
				printf("%d%c", d[i], i == 3 ? '\n' : ' ');
			}
			fflush(stdout);

		} else if (c == '!') {

			c = getchar();
			if (c != ' ') caracter_inesperado(c);

			int distancia = 0;
			int i = i1, j = j1;
			while (1) {
				distancia++;
				c = getchar();
				/**/ if (c == 'U') i -= 1;
				else if (c == 'D') i += 1;
				else if (c == 'L') j -= 1;
				else if (c == 'R') j += 1;
				else if (c == '\n') break;
				else caracter_inesperado(c);
			}

			if (i == i2 && j == j2) {
				fprintf(stderr, "El robot llego a su destino.\n");
				fprintf(stderr, "Operaciones realizadas: %d, Distancia recorrida: %d\n", operaciones, distancia);
				return EXIT_SUCCESS;
			} else {
				fprintf(stderr, "El robot no llego a su destino. Posicion final: (%d, %d).\n", i, j);
				return EXIT_FAILURE;
			}

		} else {
			caracter_inesperado(c);
		}
	}
}
