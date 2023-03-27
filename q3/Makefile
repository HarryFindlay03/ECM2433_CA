CC = gcc

demo_shuffle: demo_shuffle.o shuffle.o
	gcc -o demo_shuffle demo_shuffle.o shuffle.o  -lgsl -lgslcblas -lm

beggar: beggar.o
	gcc -o beggar beggar.o -lgsl -lgslcblas -lm

single: single.o beggar.o
	gcc -o single single.o beggar.o

byn: byn.o beggar.o
	gcc -o byn byn.o beggar.o
