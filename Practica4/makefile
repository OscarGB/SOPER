COMPILE = gcc -g -c  
LINK = gcc -g -o
EXEC = cadena_montaje
THREAD = -lpthread

all: $(EXEC)

cadena_montaje: cadena_montaje.c
	$(COMPILE) cadena_montaje.c
	$(LINK) cadena_montaje cadena_montaje.o

clean:
	rm -rf *.o $(EXEC) *.log