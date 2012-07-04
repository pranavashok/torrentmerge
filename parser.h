/*
 * parser.h
 *
 *  Created on: Jul 1, 2012
 *      Author: pranav
 */

#ifndef PARSER_H_
#define PARSER_H_

typedef struct bencode_dict {
	char* key;
	long long len;
	struct bencode_node* value;
	struct bencode_dict* next;
} bencode_dict;

typedef struct bencode_node {
	int type;
	long long len;
	union {
		long long i;
		char* s;
		struct bencode_node* l;
		struct bencode_dict* d;
	} content;
	struct bencode_node* next;
} bencode_node;

char* read_from_file(char* file);
long bencode_parse_len(char* bytes);
long bencode_parse_number(char* bytes);
struct bencode_dict* bencode_parse_dict(char* bytes);
struct bencode_node* bencode_parse(char* bytes);

#endif /* PARSER_H_ */

