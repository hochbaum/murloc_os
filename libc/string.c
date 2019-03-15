#include "string.h"

void *memset(void *ptr, const int val, const size_t num)
{
	uint8_t *base = (uint8_t *) ptr;
	uint8_t val_base = (uint8_t) (val & 0xFF);

	for (uint8_t *p = base; p < base + num; ++p)
	{
		*p = val_base;
	}

	return ptr;
}

void *memcpy(void *dest, const void *src, const size_t num)
{
	uint8_t *to = (uint8_t *) dest;
	uint8_t *from = (uint8_t *) src;

	for (size_t size = 0; size < num; size++)
	{
		*to++ = *from++;
	}

	return dest;
}
