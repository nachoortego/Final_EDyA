# Nombre del ejecutable
TARGET = programa

# Archivos fuente
SRC = main.c mapa.c glist.c pila.c punto.c camino.c tablahash.c info.c robot.c

# Archivos de encabezado
HEADERS = mapa.h glist.h pila.h punto.h camino.h tablahash.h info.h robot.h

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
main.o: main.c camino.h
glist.o: glist.c glist.h
pila.o: pila.c pila.h glist.h
tablahash.o: tablahash.c tablahash.h
punto.o: punto.c punto.h
info.o: info.c info.h
mapa.o: mapa.c mapa.h info.h
robot.o: robot.c robot.h pila.h punto.h tablahash.h info.h
camino.o: camino.c camino.h mapa.h robot.h
