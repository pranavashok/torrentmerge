/*
file.c

Author : Clive Verghese <me@cliveverghese.com>
*/

#ifndef FILE_H

#define FILE_H

typedef struct file_chunks_t{
	unsigned char content[20];
	struct file_chunks_t *next;
}file_chunks_t;
	
typedef struct file_list_t{
	char *file;
	struct file_list_t *next;
}file_list_t;

#endif
