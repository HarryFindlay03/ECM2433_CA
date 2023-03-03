CC = gcc

test_pig: pig.o test_pig.o
	gcc $^ -o test_pig

piglatin: pig.o piglatin.o
	gcc $^ -o piglatin

pig.o: pig.c pig.h
	gcc -c $<

test_pig.o: test_pig.c test_pig.h
	gcc -c $<

piglatin.o: piglatin.c
	gcc -c $<
