#include <stdlib.h>
#include <stdio.h>
#include "glist.h"
#include "pila.h"

/**
 * Crea una nueva pila vacía
*/
Pila pila_crear() {
  return glist_crear();
}

/**
 * Destruye la pila y libera la memoria
*/
void pila_destruir(Pila pila, FuncionDestructora destroy) {
  glist_destruir(pila, destroy);
}

/**
 * Verifica si la pila está vacía
*/
int pila_es_vacia(Pila pila) {
  return glist_vacia(pila);
}

/**
 * Obtiene el tope de la pila
*/
void* pila_tope(Pila pila) {
  if (pila_es_vacia(pila)) {
    return NULL;  // Devuelve NULL si la pila está vacía
  }
  return pila->data;
}

/**
 * Apila un nuevo elemento en la pila
*/
Pila pila_apilar(Pila pila, void* dato, FuncionCopia copy) {
  return glist_agregar_inicio(pila, dato, copy);
}

/**
 * Desapila el elemento en el tope de la pila
*/
Pila pila_desapilar(Pila pila, FuncionDestructora destroy) {
  if (!pila_es_vacia(pila)) {
    GNode* aux = pila->next;
    destroy(pila->data);
    free(pila);
    pila = aux;
  }
  return pila;
}

/**
 * Recorrido de la pila, utilizando la funcion pasada
*/
void pila_recorrer(Pila pila, FuncionVisitante visit) {
  glist_recorrer(pila, visit);
}
