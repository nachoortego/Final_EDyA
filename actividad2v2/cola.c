#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

// Función para crear una cola con una capacidad inicial
ColaP cola_crear(int capacity) {
    ColaP cp = (ColaP)malloc(sizeof(_ColaP));
    if (!cp) {
        fprintf(stderr, "Error al asignar memoria para la cola.\n");
        exit(EXIT_FAILURE);
    }

    cp->data = (Punto*)malloc(capacity * sizeof(Punto));
    if (!cp->data) {
        fprintf(stderr, "Error al asignar memoria para los datos de la cola.\n");
        free(cp);
        exit(EXIT_FAILURE);
    }

    cp->size = 0;
    cp->capacity = capacity;
    return cp;
}

// Función para insertar un nuevo elemento en la cola
void cola_insertar(ColaP cp, Punto p) {
    if (cp->size >= cp->capacity) {
        // Si la cola está llena, aumentamos su capacidad
        cp->capacity *= 2;
        cp->data = (Punto*)realloc(cp->data, cp->capacity * sizeof(Punto));
        if (!cp->data) {
            fprintf(stderr, "Error al redimensionar la memoria para los datos de la cola.\n");
            exit(EXIT_FAILURE);
        }
    }
    cp->data[cp->size++] = p; // Insertar el elemento al final
}

// Función para extraer el elemento de mayor antigüedad de la cola (FIFO)
Punto cola_extraer(ColaP cp) {
    if (cola_vacia(cp)) {
        fprintf(stderr, "Error: la cola está vacía.\n");
        exit(EXIT_FAILURE); // O manejar el error según tu lógica
    }

    Punto primero = cp->data[0];

    // Desplazar todos los elementos hacia la izquierda
    for (int i = 1; i < cp->size; i++) {
        cp->data[i - 1] = cp->data[i];
    }

    cp->size--; // Reducir el tamaño de la cola
    return primero;
}

// Función para verificar si la cola está vacía
int cola_vacia(ColaP cp) {
    return cp->size == 0;
}

// Función para destruir la cola y liberar la memoria
void cola_destruir(ColaP cp) {
    if (cp) {
        free(cp->data);
        free(cp);
    }
}
