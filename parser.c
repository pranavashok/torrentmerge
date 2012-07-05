/*
 * parser.c
 *
 *  Created on: Jul 1, 2012
 *      Author: pranav
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "parser.h"

unsigned char* read_from_file(char* file) {
	char *bytes;
	long int pos;
	FILE *f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	pos = ftell(f);
	fseek(f, 0, SEEK_SET);
	bytes = malloc(pos);
	fread(bytes, pos, 1, f);
	fclose(f);
	return bytes;
}

bencode_node* sha1_hash_parse(unsigned char* bytes) {
	unsigned char **pieces;
	long long i;
	bencode_node* n;
	n = (bencode_node *)malloc(sizeof(bencode_node));
	memset(n, 0, sizeof(n));
	n->type = HASH;
	long long len = bencode_parse_number(bytes);
	while(*(bytes++) != ':');
	pieces = (unsigned char **)malloc(sizeof(unsigned char*)*len/20);
	for(i = 0; i < len/20; i = i++) {
		pieces[i] = (unsigned char*)malloc(20*sizeof(unsigned char));
		bzero(pieces[i], 20);
		memcpy(pieces[i], bytes+i*20, 20);
	}
	n->content.h = pieces;
	len = sizeof(n->content.h);
	n->len = len + 1 + (len == 0 ? 1 : (int)(log10(len)+1));
	bytes += n->len;
	return n;
}

long bencode_parse_len(unsigned char* bytes) {
	long i = 0;
	while(bytes[i] != 'e')
		i++;
	return i-1;
}

long bencode_parse_number(unsigned char* bytes) {
	int i = 0;
	long n;
	if(isdigit(bytes[i])) {
		n = atoll(&bytes[i]);
	}
	return n;
}

bencode_dict* bencode_parse_dict(unsigned char* bytes) {
	int i = 0;
	long len, keylen, dictlen = 0;
	bencode_dict *start, *it;

	start = NULL;
	while(*bytes!='e') {
		len = 0;
		it = (bencode_dict *)malloc(sizeof(bencode_dict));
		memset(it, 0, sizeof(it));
		keylen = bencode_parse_number(bytes);
		while(*(bytes++)!=':') len++; //Counts number of digits also
		it->key = (unsigned char *)malloc(keylen);
		memcpy(it->key, bytes, keylen);
		bytes+=keylen;
		if(!strcmp(it->key, "pieces")) {
			sha1_hash_parse(bytes);
		}
		it->value = (bencode_node *)bencode_parse(bytes);
		dictlen += it->value->len + keylen + 1 + len;
		bytes += it->value->len;
		it->next = start;
		start = it;
	}
	start->len = dictlen;
	return start;
}

bencode_node* bencode_parse_list(unsigned char* bytes) {
	int i = 0;
	long len, listlen = 0;
	bencode_node *start, *it;

	start = NULL;
	while(*bytes!='e') {
		it = (bencode_node*)bencode_parse(bytes);
		listlen += it->len;
		bytes += it->len;
		it->next = start;
		start = it;
	}
	start->len = listlen;
	return start;
}

long long bencode_parse_integer(unsigned char* bytes) {
	int i = 0;
	long long n = 0;
	if(isdigit(bytes[i])) {
		n = atoll(&bytes[i]);
	}
	return n;
}

unsigned char* bencode_parse_string(unsigned char* bytes) {
	unsigned char *string;
	long long len = bencode_parse_number(bytes);
	while(*(bytes++) != ':');
	string = (unsigned char *)malloc(len);
	bzero(string, len+1);
	memcpy(string, bytes, len);
	return string;
}

struct bencode_node* bencode_parse(unsigned char* bytes) {
	bencode_node *n;

	long pos, i, j, len;

	switch(*bytes) {
		case 'd':	{
					n = (bencode_node *)malloc(sizeof(bencode_node));
					memset(n, 0, sizeof(n));
					n->type = DICTIONARY;
					n->content.d = bencode_parse_dict(++bytes);
					len = n->content.d->len;
					n->len = len+2;
					bytes += n->len;
					return n;
				}
		case 'l':	{
					n = (bencode_node *)malloc(sizeof(bencode_node));
					memset(n, 0, sizeof(n));
					n->type = LIST;
					n->content.l = bencode_parse_list(++bytes);
					len = n->content.l->len;
					n->len = len+2;
					bytes += n->len;
					return n;
				}
		case 'i': 	{
					n = (bencode_node *)malloc(sizeof(bencode_node));
					memset(n, 0, sizeof(n));
					n->type = INTEGER;
					n->content.i = bencode_parse_integer(++bytes);
					n->len = 2 + (n->content.i == 0 ? 1 : (int)(log10(n->content.i)+1));
					bytes += n->len;
					return n;
				}
		case '0'...'9':	{
					n = (bencode_node *)malloc(sizeof(bencode_node));
					memset(n, 0, sizeof(n));
					n->type = STRING;
					n->content.s = bencode_parse_string(bytes);
					len = strlen(n->content.s);
					n->len = len + 1 + (len == 0 ? 1 : (int)(log10(len)+1));
					bytes += n->len;
					return n;
				}
		case 'e':		{
					return NULL;
				}

	}
}

