/*
file.c

Author : Clive Verghese <me@cliveverghese.com>
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "parser.h"
#include "file.h"

//Block size in KB
#define BLOCKSIZE 265

struct file_chunk_hash* get_current_hash(file_list *ptr)
{
/*
 * Parameter is a linked list of file names.
 * Returns a linked list of the SHA1 hashes. Some of the hashes maybe spread over multiple files.
 */
    
	FILE *fptr;
	int i, bytes_read, bytes_read_next, chunk_size = 1024*BLOCKSIZE;
	struct file_chunk_hash **scan, *new, *head = NULL;
	unsigned char chunk[chunk_size], msg_digest[20];
	
	fptr = fopen(ptr->file, "r");
	while(fptr && bytes_read > 0) {
	    bytes_read = fread((void *)chunk, sizeof(char), chunk_size, fptr);
	    
	    /* 
	     * If a file gets over before chunk size is read, the next file is taken and the first
	     * chunk_size - (bytes_read from first file) is taken to form the hash. There can also 
	     * arise a case where multiple files come inside one piece.
	     */
	    
	    while(bytes_read < chunk_size && ptr->next != NULL) {
		ptr = ptr->next;
		fptr = fopen(ptr->file, "r");
		bytes_read_next = fread((void *)chunk+bytes_read, sizeof(char), chunk_size - bytes_read, fptr);
		bytes_read += bytes_read_next;
	    }
	    
	    if(bytes_read > chunk_size) 
		exit(-1);
	    
	    SHA1(chunk, bytes_read, msg_digest);
	    new = malloc(sizeof(file_chunk_hash));
	    memcpy(new->content, msg_digest, 20);
	    new->next = NULL;
	    scan = &head;
	    while(*scan != NULL)
		scan = &(*scan)->next;
	    *scan = new;
	}
	return head;
}

struct file_list* get_file_list(bencode_node *n) {
	struct bencode_node *file, *path;
	struct bencode_dict *info, *files;
	struct file_list *f_list = NULL, *f_tmp, *f_iter;
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
	return f_list;
}
	
