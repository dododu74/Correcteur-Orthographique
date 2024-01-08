# Compilation des fichiers pour construire le jeu.
#
#

all : main.o # FILE2.o
	gcc -o prog -std=c99 -Wall -Wextra -Wvla -O0 -c main.c
# gcc -o prog -std=c99 -Wall -Wextra -Wvla -O0 -o main.o FILE2.o ----- Si on a plusieurs fichiers

main.o : 
	gcc -o main.o -c main.c

#FILE2.o
#	gcc -o FILE2.o -c main.c

dev : all
	./prog

clean :
	rm -rf *.o

propre : clean
	rm -rf prog