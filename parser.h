/*
 * parser.h
 *
 *  Created on: Jul 1, 2012
 *      Author: pranav
 */

#ifndef PARSER_H_
#define PARSER_H_

enum {
	INTEGER,
	STRING,
	LIST,
	DICTIONARY,
};

typedef struct bencode_dict {
	unsigned char* key;
	long long len;
	struct bencode_node* value;
	struct bencode_dict* next;
} bencode_dict;

typedef struct bencode_node {
	int type;
	long long len;
	union {
		long long i;
		unsigned char* s;
		struct bencode_node* l;
		struct bencode_dict* d;
	} content;
	struct bencode_node* next;
} bencode_node;

typedef struct bencode_string {
	long long len;
	unsigned char* s;
} bencode_string;

unsigned char* read_from_file(char* file);
long bencode_parse_len(unsigned char* bytes);
long bencode_parse_number(unsigned char* bytes);
struct bencode_dict* bencode_parse_dict(unsigned char* bytes);
struct bencode_node* bencode_parse(unsigned char* bytes);
struct bencode_dict* get_dict_node_by_key(bencode_dict* d, char* key);

#endif /* PARSER_H_ */

