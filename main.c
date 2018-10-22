#include "ft_malloc.h"

void    *ft_malloc(size_t size)
{
    char *ptr;

    ptr = malloc(size);
    for (int i = 0; i < size; i++)
        ptr[i] = 'a';
    return ((void*)ptr);
}

int main()
{
    char *ptr1, *ptr2, *ptr3;

    ptr1 = ft_malloc(120);
    ptr2 = ft_malloc(100);
    ptr3 = ft_malloc(34);
    show_alloc_mem();
    free(ptr3);
    if ((ptr2 = realloc(ptr2 + 1, 130))) {
        for (int i = 0; i < 130; i++)
            ptr2[i] = 'b';
    }
    free(ptr2);
    show_alloc_mem();
    show_alloc_mem_hex();
}