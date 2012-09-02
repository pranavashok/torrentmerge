all:
	gcc parser.c main.c file.c -lm -lssl -lcrypto -o main
main:
	gcc parser.c main.c file.c -lm -lssl -lcrypto -o main
debug:
	gcc -g parser.c main.c file.c -lm -lssl -lcrypto -o debug
clean:
	rm -f parser file main debug
