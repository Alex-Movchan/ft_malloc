#include "ft_malloc.h"

int main()
{
    char * ptr;
    char c = 65;
    ptr = malloc(10);
    for(int j = 0; j < 1000; ++j)
    {
       char *s = malloc(1000);
    }
    char *str = malloc(100);
    for (int i = 0; i < 50; ++i)
        str[i] = ++c;
    free(ptr);
    free(str);
    return 0;
}