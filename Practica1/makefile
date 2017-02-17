COMPILE = gcc -g -c  
LINK = gcc -g -o
EXEC = ejercicio4a ejercicio4b ejercicio5a ejercicio5b

all: $(EXEC)

ejercicio4a: ejercicio4.c
	$(COMPILE) ejercicio4.c
	$(LINK) ejercicio4a ejercicio4.o

ejercicio4b: ejercicio4b.c
	$(COMPILE) ejercicio4b.c
	$(LINK) ejercicio4b ejercicio4b.o

ejercicio5a: ejercicio5a.c
	$(COMPILE) ejercicio5a.c
	$(LINK) ejercicio5a ejercicio5a.o

ejercicio5b: ejercicio5b.c
	$(COMPILE) ejercicio5b.c
	$(LINK) ejercicio5b ejercicio5b.o

clean:
	rm -rf *.o $(EXEC)