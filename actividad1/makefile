# Nombre del ejecutable
TARGET = programa

# Archivos fuente
SRC = main.c mapa.c glist.c pila.c

# Archivos de encabezado
HEADERS = mapa.h glist.h pila.h

# Compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -Werror

# Regla para compilar el ejecutable
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) *.o

# Dependencias
main.o: main.c mapa.h glist.h pila.h
mapa.o: mapa.c mapa.h
glist.o: glist.c glist.h
pila.o: pila.c pila.h glist.h
