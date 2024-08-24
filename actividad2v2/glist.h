#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado) (void *dato);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Devuelve una lista vacía.
 * 
 * @return Un puntero a una lista vacía.
 */
GList glist_crear();

/**
 * Destrucción de la lista.
 * 
 * @param lista La lista a destruir.
 * @param destruir Función que se usará para liberar la memoria de cada elemento de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 * 
 * @param lista La lista a verificar.
 * @return 1 si la lista está vacía, 0 en caso contrario.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 * 
 * @param lista La lista a la que se agregará el elemento.
 * @param dato Un puntero al dato que se desea agregar.
 * @param copiar Función que se usará para copiar el dato a la lista.
 * @return Un puntero a la lista con el nuevo elemento agregado.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorre la lista, utilizando la función pasada.
 * 
 * @param lista La lista a recorrer.
 * @param visitar Función que se aplicará a cada elemento de la lista.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

#endif /* __GLIST_H__ */
