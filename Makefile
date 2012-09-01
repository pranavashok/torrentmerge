all:
	gcc parser.c main.c -lm -o parser
	gcc file.c -lcrypto -lssl -o file
main:
	gcc parser.c main.c -lm -o parser
file:
	gcc file.c -lcrypto -lssl -o file
debug:
	gcc -g parser.c main.c -lm -o debug
clean:
	rm -f parser file debug
