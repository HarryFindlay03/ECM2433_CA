CC = gcc

demo_shuffle: demo_shuffle.o riffle.o
	gcc $^ -o demo_shuffle

demo_shuffle.o: demo_shuffle.c demo_shuffle.h
	gcc -c $<

riffle.o: riffle.c riffle.h
	gcc -c $<
