/*
 * sha1utils.h
 *
 *  Created on: Jul 8, 2012
 *      Author: pranav
 */

#ifndef SHA1UTILS_H_
#define SHA1UTILS_H_

char* hex_encode(unsigned char* str, long long len);
char** sha1_hash_parse(unsigned char* string);

#endif /* SHA1UTILS_H_ */
