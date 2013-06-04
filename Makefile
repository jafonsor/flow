main: GraphFlow.o
	gcc -ansi -Wall -pedantic -o flow main.c
	
GraphFlow.o:
	gcc -ansi -Wall -pedantic -c GraphFlow.c 
