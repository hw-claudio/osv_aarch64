#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>
#include "libc.h"

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) (((x)-ONES) & ~(x) & HIGHS)

char *__stpcpy(char *__restrict d, const char *__restrict s)
{
	size_t *wd;
	const size_t *ws;

	if ((uintptr_t)s % ALIGN == (uintptr_t)d % ALIGN) {
		for (; (uintptr_t)s % ALIGN; s++, d++)
			if (!(*d=*s)) return d;
		wd=(void *)d; ws=(const void *)s;
		for (; !HASZERO(*ws); *wd++ = *ws++);
		d=(void *)wd; s=(const void *)ws;
	}
	for (; (*d=*s); s++, d++);

	return d;
}

weak_alias(__stpcpy, stpcpy);

/* Used by code compiled on Linux with -D_FORTIFY_SOURCE */
char *__stpcpy_chk (char *dest, const char *src, size_t destlen)
{
    // TODO: This repeats some of stpcpy's work. Make it more efficent.
    assert(strlen(src) < destlen);
    return stpcpy(dest, src);
}
