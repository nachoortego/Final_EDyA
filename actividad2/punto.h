#ifndef __PUNTO_H__
#define __PUNTO_H__

/**
 * Estructura de Punto para representar coordenadas
 * Tiene un valor entero x
 * Tiene un valor entero y
 */
typedef struct {
  int x, y;
} Punto;

/**
 * Función hash para la estructura Punto.
 * Retorna un valor hash para el punto (x, y).
 */
unsigned hash_punto(void* punto);

/**
 * Función de comparación para la estructura Punto.
 * Retorna 0 si los puntos son iguales, y un valor distinto de 0 si no lo son.
 */
int comparar_puntos(void* p1, void* p2);

/**
 * Función para copiar un punto.
 * Retorna un nuevo punto con los mismos valores.
 */
void* copiar_punto(void* punto);

/**
 * Función destructora para liberar un punto.
 */
void destruir_punto(void* punto);

#endif /* __PUNTO_H__ */
