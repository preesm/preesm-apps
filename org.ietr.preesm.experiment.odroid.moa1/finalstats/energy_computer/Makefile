all: energy_computer

energy_computer: main.o
	gcc -o energy_computer main.o

main.o: main.c
	gcc -o main.o -c main.c -W -Wall

clean:
	rm *.o
