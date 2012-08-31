/*
file.c

Author : Clive Verghese <me@cliveverghese.com>
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "file.h"

file_chunks_t * parse_file(file_list_t *ptr)
{
	FILE *fptr;
	int i, bytes_read, chunk_size = 1024;
	struct file_chunks_t **scan, *new, *head = NULL;
	unsigned char chunk[1024], msg_digest[20];
	
	fptr = fopen(ptr->file,"r");
	while(fptr && bytes_read > 0) {
	    bytes_read = fread((void *)chunk, sizeof(char), chunk_size, fptr);
	    SHA1(chunk, bytes_read, msg_digest);
	    new = malloc(sizeof(file_chunks_t));
	    memcpy(new->content, msg_digest, 20);
	    new->next = NULL;
	    scan = &head;
	    while(*scan != NULL)
		scan = &(*scan)->next;
	    *scan = new;
	}
	return head;
}

int main(int argc,char *argv[])
{
	struct file_list_t file_list;
	struct file_chunks_t *ptr;
	int i;
	file_list.file = calloc(1024,sizeof(char));
	strcpy(file_list.file,argv[1]);
	printf("%s\n",file_list.file);
	ptr = parse_file(&file_list);
	printf("\n");
	do {
	    for(i = 0; i < 20; i++)
	    {
		    printf("%02x",ptr->content[i]);
	    }
	    printf("\n");
	} while (ptr = ptr->next);
	printf("\n");
	return 0;
}
	
	
	
	
	
	
