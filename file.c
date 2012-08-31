/*
file.c

Author : Clive Verghese <me@cliveverghese.com>
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "file.h"

//Block size in KB
#define BLOCKSIZE 265

file_chunk_hash* get_current_hash(file_list *ptr)
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

int main(int argc,char *argv[])
{
	struct file_list file_list;
	struct file_chunk_hash *ptr;
	int i;
	file_list.file = calloc(1024, sizeof(char));
	strcpy(file_list.file,argv[1]);
	printf("%s\n",file_list.file);
	file_list.next = NULL;
	ptr = get_current_hash(&file_list);
	printf("\n");
	do {
	    for(i = 0; i < 20; i++)
	    {
		    printf("%02x", ptr->content[i]);
	    }
	    printf("\n");
	} while (ptr = ptr->next);
	printf("\n");
	return 0;
}
	
	
	
	
	
	
