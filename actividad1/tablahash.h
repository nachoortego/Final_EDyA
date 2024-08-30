#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "glist.h"

typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia física del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2 */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */

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


typedef struct _TablaHash *TablaHash;

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
                          FuncionHash hash);

/**
 * Retorna el número de elementos de la tabla.
 * 
 * @param tabla La tabla hash de la cual se desea obtener el número de elementos.
 * @return El número de elementos en la tabla.
 */
int tablahash_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 * 
 * @param tabla La tabla hash de la cual se desea obtener la capacidad.
 * @return La capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla y libera la memoria asociada.
 * 
 * @param tabla La tabla hash a destruir.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * 
 * @param tabla La tabla hash en la cual se desea insertar el dato.
 * @param dato El dato a insertar o reemplazar en la tabla.
 */
void tablahash_insertar(TablaHash tabla, void *dato);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 * 
 * @param tabla La tabla hash en la cual se desea buscar el dato.
 * @param dato El dato a buscar en la tabla.
 * @return Un puntero al dato encontrado, o NULL si no se encuentra el dato.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 * 
 * @param tabla La tabla hash de la cual se desea eliminar el dato.
 * @param dato El dato a eliminar de la tabla.
 */
void tablahash_eliminar(TablaHash tabla, void *dato);

#endif /* __TABLAHASH_H__ */
