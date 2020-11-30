#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>

void sha256_calc(char* data, int len, char result[32]);

//example
	//char test[] = "123456789";
	//char result[32];
	//int i;
	//sha256_calc(test, 9, result);
	//for (i = 0; i < 32; i++)
	//	printf("%X", result[i] & 0xff);

#endif
