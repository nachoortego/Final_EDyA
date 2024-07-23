#ifndef __PILA_H__
#define __PILA_H__

#include "glist.h"

typedef GList Pila;

/**
 * Crea una nueva pila vacía.
 * 
 * @return Un puntero a una nueva pila vacía.
 */
Pila pila_crear();

/**
 * Destruye la pila y libera la memoria.
 * 
 * @param pila La pila a destruir.
 * @param destroy Función que se usará para liberar la memoria de cada elemento de la pila.
 */
void pila_destruir(Pila pila, FuncionDestructora destroy);

/**
 * Verifica si la pila está vacía.
 * 
 * @param pila La pila a verificar.
 * @return 1 si la pila está vacía, 0 en caso contrario.
 */
int pila_es_vacia(Pila pila);

/**
 * Obtiene el tope de la pila.
 * 
 * @param pila La pila de la que se obtendrá el tope.
 * @return Un puntero al dato en el tope de la pila, o NULL si la pila está vacía.
 */
void* pila_tope(Pila pila);

/**
 * Apila un nuevo elemento en la pila.
 * 
 * @param pila La pila en la que se apilará el nuevo elemento.
 * @param dato Un puntero al dato que se desea apilar.
 * @param copy Función que se usará para copiar el dato a la pila.
 * @return Un puntero a la pila con el nuevo elemento apilado.
 */
Pila pila_apilar(Pila pila, void* dato, FuncionCopia copy);

/**
 * Desapila el elemento en el tope de la pila.
 * 
 * @param pila La pila de la que se desapilará el elemento.
 * @param destroy Función que se usará para liberar la memoria del dato desapilado.
 * @return Un puntero a la pila con el elemento desapilado.
 */
Pila pila_desapilar(Pila pila, FuncionDestructora destroy);

/**
 * Recorre la pila, utilizando la función pasada.
 * 
 * @param pila La pila a recorrer.
 * @param visit Función que se aplicará a cada elemento de la pila.
 */
void pila_recorrer(Pila pila, FuncionVisitante visit);

#endif /* __PILA_H__ */
