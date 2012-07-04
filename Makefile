all:
	gcc parser.c main.c -o main -lm
	gcc -g parser.c main.c -o debug -lm
main:
	gcc parser.c main.c -o main -lm
debug:
	gcc -g parser.c main.c -o debug -lm
clean:
	rm main debug
