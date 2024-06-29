#include <stdlib.h>
#include <stdio.h>
#include "glist.h"
#include "pila.h"

Pila pila_crear() {
  return glist_crear();
}

void pila_destruir(Pila pila, FuncionDestructora destroy) {
  glist_destruir(pila, destroy);
}

int pila_es_vacia(Pila pila) {
  return glist_vacia(pila);
}

void* pila_tope(Pila pila) {
  if (pila_es_vacia(pila)) {
    return NULL;  // Devuelve NULL si la pila está vacía
  }
  return pila->data;
}

Pila pila_apilar(Pila pila, void* dato, FuncionCopia copy) {
  return glist_agregar_inicio(pila, dato, copy);
}

Pila pila_desapilar(Pila pila, FuncionDestructora destroy) {
  if (!pila_es_vacia(pila)) {
    GNode* aux = pila->next;
    destroy(pila->data);
    free(pila);
    pila = aux;
  }
  return pila;
}

void pila_imprimir(Pila pila, FuncionVisitante visit) {
  glist_recorrer(pila, visit);
}
