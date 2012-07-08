/*
 * sha1utils.c
 *
 *  Created on: Jul 8, 2012
 *      Author: pranav
 */


char* hex_encode(unsigned char* str, long long len) {
    char* tmp = (char *)malloc(sizeof(char));
    const char *c = str;
    char buf[3];
    long long i = 0;
    while(i < len) {
        sprintf(buf, "%02X", (unsigned char) *c);
        tmp = realloc(tmp, strlen(tmp)+2*sizeof(char)+1);
        strcat(tmp, buf);
        i++;
        c++;
    }
    return tmp;
}
char** sha1_hash_parse(unsigned char* string) {
	char **pieces;
	long long i;
	long long len = bencode_parse_number(string);
	while(*(string++) != ':');
	pieces = (char **)malloc(sizeof(char*)*len/20);
	for(i = 0; i < len/20; i = i++) {
		pieces[i] = (char *)malloc(20*sizeof(char));
		bzero(pieces[i], 20);
		memcpy(pieces[i], string+i*20, 20);
	}
	return pieces;
}
