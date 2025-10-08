#include <stdlib.h>
#include "libft.h"

void *gc_malloc(size_t size)
{
    return malloc(size);
}

char *gc_substr(char *s, unsigned int start, size_t len)
{
    // nutze libft-Implementierung
    return ft_substr(s, start, len);
}
