#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>

void sha256_calc(char* data, int len, char result[32]);
int sha256_confirm(char* data, int len, char sha2[32]);

#endif
