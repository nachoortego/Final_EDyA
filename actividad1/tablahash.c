#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define LOAD_FACTOR 0.75

TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con listas vacías.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].lista = glist_crear();
  }

  return tabla;
}

int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

void tablahash_destruir(TablaHash tabla) {

  // Destruir cada una de las listas en las casillas.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    glist_destruir(tabla->elems[idx].lista, tabla->destr);
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

void rehash(TablaHash tabla, unsigned nueva_capacidad) {
  // Crear una nueva tabla hash con la nueva capacidad.
  TablaHash nueva_tabla = tablahash_crear(nueva_capacidad, tabla->copia, tabla->comp, tabla->destr, tabla->hash);

  // Reinsertar todos los elementos en la nueva tabla.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    GList lista = tabla->elems[idx].lista;
    for (GNode *node = lista; node != NULL; node = node->next)
      tablahash_insertar(nueva_tabla, node->data);
  }

  // Destruir la tabla original.
  tablahash_destruir(tabla);

  // Actualizar la tabla original para que apunte a la nueva tabla.
  *tabla = *nueva_tabla;
  free(nueva_tabla);
}

void tablahash_insertar(TablaHash tabla, void *dato) {

  // Rehash si el factor de carga supera el umbral.
  if ((float)tabla->numElems / tabla->capacidad > LOAD_FACTOR)
    rehash(tabla, tabla->capacidad * 2);

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Buscar el dato en la lista.
  GList lista = tabla->elems[idx].lista;
  for (GNode *node = lista; node != NULL; node = node->next) {
    if (tabla->comp(node->data, dato) == 0) {
      tabla->destr(node->data);
      node->data = tabla->copia(dato);
      return;
    }
  }

  // Si no se encontró, agregar al inicio de la lista.
  tabla->elems[idx].lista = glist_agregar_inicio(tabla->elems[idx].lista, dato, tabla->copia);
  tabla->numElems++;
}

void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Buscar el dato en la lista.
  GList lista = tabla->elems[idx].lista;
  for (GNode *node = lista; node != NULL; node = node->next) {
    if (tabla->comp(node->data, dato) == 0)
      return node->data;
  }
  return NULL;
}

void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Buscar y eliminar el dato en la lista.
  GList lista = tabla->elems[idx].lista;
  GNode *prev = NULL;
  for (GNode *node = lista; node != NULL; node = node->next) {
    if (tabla->comp(node->data, dato) == 0) {
      if (prev == NULL) {
        tabla->elems[idx].lista = node->next;
      } else {
        prev->next = node->next;
      }
      tabla->destr(node->data);
      free(node);
      tabla->numElems--;
      return;
    }
    prev = node;
  }
}