#	Makefile para compilar archivos en el directorio actual
#	Nombre del ejecutable. Preferiblemente en Mayusculas

TARGET = RUN
#	Bibliotecas incluidas. La biblioteca math es muy comun
LIBS = -lm
#	Compilador utilizado. Por ejemplo icc, pgcc, gcc
CC = g++
#	Banderas del compilador
CFLAGS = -g -Wall

#	Palabras que usa Makefile que podrian ser el nombre de un programa
.PHONY: default all clean
#	Compilacion por defecto

default: $(TARGET)
all: default
#	Incluyen los archivos .o y .cpp que estan en el directorio actual
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
#	Incluyen los archivos .h (ó .hpp)que estan en el directorio actual
HEADERS = $(wildcard *.hpp)
#	Compila automaticamente solo archivos fuentes que se han modificado
#	$< es el primer prerrequisito, generalmente el archivo fuente
#	$@ nombre del archivo que se esta Generando, archivo objeto
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
#	Preserva archivos intermedios
.PRECIOUS: $(TARGET) $(OBJECTS)

#	Enlaza objetos y crea el ejecutable
$(TARGET):$(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) $(HEADERS) -o $@
#	Borra archivos .o
clean:
	-rm -f *.o core
# 	Borra archivos .o y el ejecutable
cleanall: clean
	-rm -f $(TARGET)
