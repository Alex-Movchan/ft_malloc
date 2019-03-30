#include "ft_malloc.h"

int main()
{
    char * ptr;
    char c = 65;
    ptr = malloc(10);

    char *str = malloc(3223);
    for (int i = 0; i < 50; ++i)
        str[i] = ++c;
    free(ptr);
    free(str);
    return 0;
}