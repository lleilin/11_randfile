main: main.o
	gcc -o main main.c

main.o: main.c
	gcc -c main.c

.PHONY: clean run

clean:
	-rm *.o *.out main

run:
	./main
