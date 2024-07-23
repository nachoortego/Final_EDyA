# Nombre del ejecut del ejecutable
TARGET = robot

# Archivos fuente
SRC = main.c mapa.c glist.c pila.c array.c tablahash.c punto.c

# Archivos de encabezado
HEADERS = mapa.h glist.h pila.h array.h tablahash.h punto.h

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
mapa.o: mapa.c mapa.h tablahash.h punto.h
glist.o: glist.c glist.h
pila.o: pila.c pila.h glist.h
array.o: array.c array.h
tablahash.o: tablahash.c tablahash.h glist.h
punto.o: punto.c punto.h