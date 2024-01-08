# Compilation des fichiers pour construire le jeu.
#
#

all : main.o
	gcc -o prog -std=c99 -Wall -Wextra -Wvla -O0 -g main.o

main.o : 
	gcc -o main.o -c main.c

dev : all
	./prog

clean :
	rm -rf *.o

propre : clean
	rm -rf prog