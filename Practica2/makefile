COMPILE = gcc -g -c  
LINK = gcc -g -o
EXEC = ejercicio3a ejercicio3b
THREAD = -lpthread

all: $(EXEC)

ejercicio3a: ejercicio3a.c
	$(COMPILE) ejercicio3a.c
	$(LINK) ejercicio3a ejercicio3a.o 

ejercicio3b: ejercicio3b.c
	$(COMPILE) ejercicio3b.c $(THREAD)
	$(LINK) ejercicio3b ejercicio3b.o $(THREAD)


clean:
	rm -rf *.o $(EXEC)