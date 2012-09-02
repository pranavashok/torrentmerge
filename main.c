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
	bencode_node *n, *file, *path;
	bencode_dict *info, *files;
	struct file_list *f_list = NULL, *f_tmp, *f_iter;
	struct file_chunk_hash *ptr;
	int i;

	printf("Parsing %s...\n", argc[1]);
	bencode = read_from_file(argc[1]);

	n = bencode_parse(bencode);
	printf("\nParsing completed");

	printf("\nListing files\n");
	info = get_dict_node_by_key(n->content.d, "info");

	files = get_dict_node_by_key(info->value->content.d, "files");

	file = files->value->content.l;
	while(file) {
		path = file->content.d->value->content.l;
		char *filepath = "";
		while(path!=NULL) {
			asprintf(&filepath, "/%s%s", path->content.s, filepath);
			path = path->next;
		}

		f_tmp = malloc(sizeof(file_list));
		f_tmp->file = calloc(strlen(filepath), sizeof(char));
		memcpy(f_tmp->file, filepath, strlen(filepath));
		f_tmp->next = NULL;

		if(f_list == NULL) {
			f_list = f_tmp;
		}
		else {
			f_tmp->next = f_list;
			f_list = f_tmp;
		}
		file=file->next;
	}
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
