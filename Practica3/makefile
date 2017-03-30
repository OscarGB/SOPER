COMPILE = gcc -g -c  
LINK = gcc -g -o
EXEC = ejercicio2 #ejercicio3a ejercicio3b ejercicio4 ejercicio6 ejercicio10 ejercicio8
THREAD = -lpthread

all: $(EXEC)

ejercicio2: ejercicio2.c
	$(COMPILE) ejercicio2.c $(THREAD)
	$(LINK) ejercicio2 ejercicio2.o $(THREAD)

ejercicio3a: ejercicio3a.c
	$(COMPILE) ejercicio3a.c
	$(LINK) ejercicio3a ejercicio3a.o 

ejercicio3b: ejercicio3b.c
	$(COMPILE) ejercicio3b.c $(THREAD)
	$(LINK) ejercicio3b ejercicio3b.o $(THREAD)

ejercicio4: ejercicio4.c
	$(COMPILE) ejercicio4.c $(THREAD)
	$(LINK) ejercicio4 ejercicio4.o $(THREAD)

ejercicio6: ejercicio6.c
	$(COMPILE) ejercicio6.c
	$(LINK) ejercicio6 ejercicio6.o 

ejercicio8: ejercicio8.c
	$(COMPILE) ejercicio8.c
	$(LINK) ejercicio8 ejercicio8.o

ejercicio10: ejercicio10.c
	$(COMPILE) ejercicio10.c
	$(LINK) ejercicio10 ejercicio10.o

clean:
	rm -rf *.o $(EXEC) *.log