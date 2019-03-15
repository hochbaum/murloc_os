#ifndef MURLOC_OS_STRING_H
#define MURLOC_OS_STRING_H

#include "stddef.h"
#include "stdint.h"

void *memset(void *ptr, const int val, const size_t num);
void *memcpy(void *dest, const void *src, const size_t num);

size_t strlen(const char *str);

void reverse(char *str);

void itoa(char *buf, const int num);

#endif //MURLOC_OS_STRING_H
