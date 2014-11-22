/* 
 * File:   mem.c
 * Author: Pietro Lorefice
 */

#include <stddef.h>
#include <stdint.h>

#include <kernel/mem.h>

/* ============================ Private constants =========================== */

/* ============================ Private variables =========================== */

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

/* ============================ Public functions ============================ */

int kmemcmp (const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p1 = (const unsigned char *) ptr1;
	const unsigned char *p2 = (const unsigned char *) ptr2;

	while (num--)
		if (*(p1++) < *(p2++))
			return -1;
		else if (*(p1++) > *(p2++))
			return 1;

	return 0;
}

void* kmemcpy (void *dst, const void *src, size_t num)
{
	unsigned char *pdst = (unsigned char *) dst;
	const unsigned char *psrc = (const unsigned char *) src;

	if (num == 0 || dst == src)
		goto done;

	while (num--)
		*(pdst++) = *(psrc++);

done:
	return (dst);
}

void* kmemmove (void *dst, const void *src, size_t num)
{
	const unsigned char *psrc = (const unsigned char *) src;
	      unsigned char *pdst = (unsigned char *) dst;

	size_t i;

	if (num == 0 || dst == src)
		goto done;

	if (dst < src)
		for (i = 0; i < num; i++)
			pdst[i] = psrc[i];
	else
		for (i = num; i != 0; i--)
			pdst[i-1] = psrc[i-1];

done:
	return (dst);
}

void* kmemset (void *dst, int val, size_t num)
{
	unsigned char *pdst = (unsigned char *) dst;
	unsigned char  v    = (unsigned char) val;

	while (num--)
		*(pdst++) = v;

	return (dst);
}

void* kmemsetw (void *dst, int val, size_t num)
{
	unsigned short *pdst = (unsigned short *) dst;
	unsigned short v = (unsigned short) val;

	while (num--)
		*(pdst++) = v;

	return (dst);
}

size_t kstrlen (const char *s)
{
	size_t n = 0;

	while (s[n]) n++;

	return n;
}
