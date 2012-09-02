/*
 * main.c
 *
 *  Created on: Jul 3, 2012
 *      Author: pranav
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "file.h"

int main(int argv, char* argc[]) {
	char* bencode;
	struct bencode_node *n;
	struct file_list *f_list, *f_iter;
	struct file_chunk_hash *ptr;
	int i;

	printf("Parsing %s...\n", argc[1]);
	bencode = read_from_file(argc[1]);

	n = bencode_parse(bencode);
	printf("\nParsing completed");

	printf("\nListing files\n");

	f_list = get_file_list(n);
	f_iter = f_list;
	while(f_iter) {
		printf("%s\n", f_iter->file);
		f_iter = f_iter->next;
	}
	/*
    ptr = get_current_hash(f_list);

    printf("\n");
    do {
	for(i = 0; i < 20; i++)
	{
	    printf("%02x", ptr->content[i]);
	}
	printf("\n");
    } while (ptr = ptr->next);
    printf("\n");
	 */
	return 0;
}
