/*
file.c

Author : Clive Verghese <me@cliveverghese.com>
*/

#ifndef FILE_H

#define FILE_H

typedef struct file_chunk_hash {
	unsigned char content[20];
	struct file_chunk_hash *next;
} file_chunk_hash;
	
typedef struct file_list {
	char *file;
	struct file_list *next;
}file_list;

struct file_chunk_hash* get_current_hash(file_list *ptr);

#endif
