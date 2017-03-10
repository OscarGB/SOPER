COMPILE = gcc -g -c  
LINK = gcc -g -o
EXEC = ejercicio3a ejercicio3b

all: $(EXEC)

ejercicio3a: ejercicio3a.c
	$(COMPILE) ejercicio3a.c
	$(LINK) ejercicio3a ejercicio3a.o

ejercicio3b: ejercicio3b.c
	$(COMPILE) ejercicio3b.c
	$(LINK) ejercicio3b ejercicio3b.o


clean:
	rm -rf *.o $(EXEC)