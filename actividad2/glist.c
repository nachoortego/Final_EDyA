#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Devuelve una lista vacía.
 * 
 * @return Un puntero a una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destrucción de la lista.
 * 
 * @param lista La lista a destruir.
 * @param destruir Función que se usará para liberar la memoria de cada elemento de la lista.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 * 
 * @param lista La lista a verificar.
 * @return 1 si la lista está vacía, 0 en caso contrario.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * 
 * @param lista La lista a la que se agregará el elemento.
 * @param dato Un puntero al dato que se desea agregar.
 * @param copiar Función que se usará para copiar el dato a la lista.
 * @return Un puntero a la lista con el nuevo elemento agregado.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorre la lista, utilizando la función pasada.
 * 
 * @param lista La lista a recorrer.
 * @param visitar Función que se aplicará a cada elemento de la lista.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}