COMPILE = gcc -g -c  
LINK = gcc -g -o
EXEC = ejercicio4a ejercicio4b ejercicio5a ejercicio5b ejercicio6 ejercicio8 ejercicio9

all: $(EXEC)

ejercicio4a: ejercicio4a.c
	$(COMPILE) ejercicio4a.c
	$(LINK) ejercicio4a ejercicio4a.o

ejercicio4b: ejercicio4b.c
	$(COMPILE) ejercicio4b.c
	$(LINK) ejercicio4b ejercicio4b.o

ejercicio5a: ejercicio5a.c
	$(COMPILE) ejercicio5a.c
	$(LINK) ejercicio5a ejercicio5a.o

ejercicio5b: ejercicio5b.c
	$(COMPILE) ejercicio5b.c
	$(LINK) ejercicio5b ejercicio5b.o

ejercicio6: ejercicio6.c
	$(COMPILE) ejercicio6.c
	$(LINK) ejercicio6 ejercicio6.o

ejercicio8: ejercicio8.c
	$(COMPILE) ejercicio8.c
	$(LINK) ejercicio8 ejercicio8.o

ejercicio9: ejercicio9.c
	$(COMPILE) ejercicio9.c
	$(LINK) ejercicio9 ejercicio9.o

clean:
	rm -rf *.o $(EXEC)