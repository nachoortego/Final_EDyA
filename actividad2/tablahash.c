#include "tablahash.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  GList lista;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
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

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
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

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * Maneja colisiones usando listas.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

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

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Buscar el dato en la lista.
  GList lista = tabla->elems[idx].lista;
  for (GNode *node = lista; node != NULL; node = node->next) {
    if (tabla->comp(node->data, dato) == 0) {
      return node->data;
    }
  }

  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
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
