CC = gcc

demo_shuffle: demo_shuffle.o shuffle.o
	gcc -o demo_shuffle demo_shuffle.o shuffle.o  -lgsl -lgslcblas -lm

beggar: beggar.o shuffle.o
	gcc -o beggar beggar.o shuffle.o -lgsl -lgslcblas -lm

single: single.o beggar.o shuffle.o
	gcc -o single single.o beggar.o shuffle.o -lgsl -lgslcblas -lm

byn: byn.o beggar.o shuffle.o
	gcc -o byn byn.o beggar.o shuffle.o -lgsl -lgslcblas -lm 

shuffle.o: shuffle.c
	gcc -c shuffle.c
