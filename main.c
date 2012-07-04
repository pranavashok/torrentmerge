/*
 * main.c
 *
 *  Created on: Jul 3, 2012
 *      Author: pranav
 */

#include <stdio.h>
#include "parser.h"
 
int main(int argv, char* argc[]) {
	char* bencode;
	printf("Parsing %s...\n", argc[1]);
	bencode = read_from_file(argc[1]);
	bencode_node *n;
	n = bencode_parse(bencode);
	return 0;
}
