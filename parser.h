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
	HASH
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
		unsigned char** h;
	} content;
	struct bencode_node* next;
} bencode_node;

unsigned char* read_from_file(char* file);
long bencode_parse_len(unsigned char* bytes);
long bencode_parse_number(unsigned char* bytes);
struct bencode_dict* bencode_parse_dict(unsigned char* bytes);
struct bencode_node* bencode_parse(unsigned char* bytes);
struct bencode_node* sha1_hash_parse(unsigned char* bytes);

#endif /* PARSER_H_ */

