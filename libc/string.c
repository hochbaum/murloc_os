#include <string.h>

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

size_t strlen(const char* str)
{
	size_t size = 0;
	for (; *str; str++)
	{
		size++;
	}

	return size;
}

void reverse(char *str)
{
	int i, j, k;
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
	{
		k = str[i];
		str[i] = str[j];
		str[j] = k;
	}
}

void itoa(char *str, int n)
{
	int sign = n;
	if (sign < 0)
	{
		n = -n;
	}

	int i = 0;
	do
	{
		str[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0)
	{
		str[i++] = '-';
	}

	str[i] = '\0';
	reverse(str);
}

char *strip(char *str)
{
	size_t len = strlen(str);
	char *p = str + len - 1;

	while (p >= str && *p == ' ')
	{
		p--;
	}

	*(p + 1) = '\0';

	while (*str && *str == ' ')
	{
		str++;
	}

	return str;
}

void tolower(char *str)
{
	for (; *str; str++)
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			*str += 32;
		}
	}
}

int strcmp(char *str1, char *str2)
{
	int i;
	for (i = 0; str1[i] == str2[i]; i++) {
		if (!str1[i])
		{
			return 0;
		}
	}

	return str1[i] - str2[i];
}
