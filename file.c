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
	int chunk_size = 1024,i;
	struct file_chunks_t *ret;
	unsigned char chunk[1024],msg_digest[20];
	
	printf("%s opened\n",ptr->file);
	fptr = fopen(ptr->file,"r");
	
	fread((void *)chunk,sizeof(char),chunk_size,fptr);
	SHA1(chunk,chunk_size,msg_digest);
	for(i = 0; i < 20; i++)
	{
		printf("%02x",msg_digest[i]);
	}
	
	ret = malloc(sizeof(file_chunks_t));
	memcpy(ret->content,msg_digest,20);
	
	
	ret->next = NULL;
	return ret;
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
	for(i = 0; i < 20; i++)
	{
		printf("%02x",ptr->content[i]);
	}
	printf("\n");
	return 0;
}
	
	
	
	
	
	
