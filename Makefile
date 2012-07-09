all:
	gcc parser.c main.c -o main -lm
	gcc -g parser.c main.c -o debug -lm
	gcc file.c -lcrypto -lssl -o file
main:
	gcc parser.c main.c -o main -lm
debug:
	gcc -g parser.c main.c -o debug -lm
clean:
	rm main debug
