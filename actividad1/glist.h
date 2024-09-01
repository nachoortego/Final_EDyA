#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void *dato);

/**
 * Estructura de nodo para la lista genérica.
 * 
 * @param data Puntero a los datos almacenados en el nodo.
 * @param next Puntero al siguiente nodo en la lista.
 */
typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Devuelve una lista vacía.
 * 
 * @return GList Una lista vacía.
 */
GList glist_crear();

/**
 * Destrucción de la lista.
 * 
 * @param lista La lista a destruir.
 * @param destruir Función destructora para liberar los datos almacenados en la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 * 
 * @param lista La lista a comprobar.
 * @return Devuelve 1 si la lista es vacía, 0 en caso contrario.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 * 
 * @param lista La lista a la que se agregará el elemento.
 * @param dato El dato a agregar a la lista.
 * @param copiar Función para copiar el dato.
 * @return GList La lista con el nuevo elemento agregado al inicio.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la función pasada.
 * 
 * @param lista La lista a recorrer.
 * @param visitar Función visitante que se aplicará a cada elemento de la lista.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

#endif /* __GLIST_H__ */