#ifndef PILA_H
#define PILA_H

#include "glist.h"

typedef GList Pila;

/**
 * Crea una nueva pila vacía
*/
Pila pila_crear();

/**
 * Destruye la pila y libera la memoria
*/
void pila_destruir(Pila pila, FuncionDestructora destroy);

/**
 * Verifica si la pila está vacía
*/
int pila_es_vacia(Pila pila);

/**
 * Obtiene el tope de la pila
*/
void* pila_tope(Pila pila);

/**
 * Apila un nuevo elemento en la pila
*/
Pila pila_apilar(Pila pila, void* dato, FuncionCopia copy);

/**
 * Desapila el elemento en el tope de la pila
*/
Pila pila_desapilar(Pila pila, FuncionDestructora destroy);

/**
 * Imprime los elementos de la pila
*/
void pila_imprimir(Pila pila, FuncionVisitante visit);

#endif // PILA_H
