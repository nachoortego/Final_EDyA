#ifndef __PUNTO_H__
#define __PUNTO_H__

/**
 * Estructura de Punto para representar coordenadas.
 * 
 * Tiene un valor entero x.
 * Tiene un valor entero y.
 */
typedef struct {
  int x, y;
} Punto;

/**
 * Función para crear un punto.
 * 
 * @param x La coordenada x del punto.
 * @param y La coordenada y del punto.
 * @return Un punto con las coordenadas (x, y).
 */
Punto crear_punto(int x, int y);

/**
 * Función hash para la estructura Punto.
 * 
 * @param punto Un puntero a la estructura Punto para la cual se calculará el valor hash.
 * @return Un valor hash calculado para el punto (x, y).
 */
unsigned hash_punto(void* punto);

/**
 * Función de comparación para la estructura Punto.
 * 
 * @param p1 Un puntero al primer punto a comparar.
 * @param p2 Un puntero al segundo punto a comparar.
 * @return 0 si los puntos son iguales, y un valor distinto de 0 si no lo son.
 */
int comparar_puntos(void* p1, void* p2);

/**
 * Función para copiar un punto.
 * 
 * @param punto Un puntero al punto que se desea copiar.
 * @return Un puntero a un nuevo punto con los mismos valores que el original.
 */
void* copiar_punto(void* punto);

/**
 * Función destructora para liberar un punto.
 * 
 * @param punto Un puntero al punto que se desea liberar.
 */
void destruir_punto(void* punto);

#endif /* __PUNTO_H__ */
