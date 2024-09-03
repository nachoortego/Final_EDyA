# Nombre del ejecut del ejecutable
TARGET = robot

# Archivos fuente
SRC = main.c algorithm.c mapa.c cola.c array.c

# Archivos de encabezado
HEADERS = algorithm.h  mapa.h cola.h array.h punto.h

# Compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -Werror

# Regla para compilar el ejecutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) *.o

# Dependencias
main.o: main.c mapa.h
algorithm.o: algorithm.c algorithm.h
mapa.o: mapa.c mapa.h punto.h cola.h
cola.o: cola.c cola.h punto.h
array.o: array.c array.h
punto.o: punto.h
