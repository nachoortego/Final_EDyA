#!/bin/sh

# Compilar el programa utilizando el Makefile
make clean
make

# Compilar el programa sensor
make sensor -s

# Crear fifo en /tmp
fifo="/tmp/feedback_fifo"
mkfifo $fifo

# Ejecutar los programas en paralelo utilizando el fifo
(./robot < $fifo | ./sensor $1 > $fifo) &

# Asegurarse de que ambos programas han terminado
wait

# Eliminar fifo
rm $fifo
