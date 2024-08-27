#include "tablahash.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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
 * Crea una nueva tabla hash vacía, con la capacidad dada.
 * 
 * @param capacidad La capacidad inicial de la tabla hash.
 * @param copia Función para copiar los datos que se almacenan en la tabla.
 * @param comp Función para comparar dos datos.
 * @param destr Función para liberar la memoria de los datos.
 * @param hash Función para calcular el valor hash de un dato.
 * @return Un puntero a la nueva tabla hash creada.
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
 * Retorna el número de elementos de la tabla.
 * 
 * @param tabla La tabla hash de la cual se desea obtener el número de elementos.
 * @return El número de elementos en la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 * 
 * @param tabla La tabla hash de la cual se desea obtener la capacidad.
 * @return La capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla y libera la memoria asociada.
 * 
 * @param tabla La tabla hash a destruir.
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
 * 
 * @param tabla La tabla hash en la cual se desea insertar el dato.
 * @param dato El dato a insertar o reemplazar en la tabla.
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
  // fprintf(stderr, "> Sensor agregado\n");
  tabla->numElems++;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 * 
 * @param tabla La tabla hash en la cual se desea buscar el dato.
 * @param dato El dato a buscar en la tabla.
 * @return Un puntero al dato encontrado, o NULL si no se encuentra el dato.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Buscar el dato en la lista.
  GList lista = tabla->elems[idx].lista;
  for (GNode *node = lista; node != NULL; node = node->next) {
    if (tabla->comp(node->data, dato) == 0) {
      // fprintf(stderr, "> Sensor encontrado\n");
      return node->data;
    }
  }
  // fprintf(stderr, "> Sensor no encontrado\n");
  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 * 
 * @param tabla La tabla hash de la cual se desea eliminar el dato.
 * @param dato El dato a eliminar de la tabla.
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
