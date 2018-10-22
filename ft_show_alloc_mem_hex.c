#include "ft_malloc.h"

static void ft_print_ascii(unsigned char *str, size_t size)
{
    int     i;

    i = -1;
    while (++i < HEX && i < (int)size)
    {
        if (ft_isprint(str[i]))
            ft_putchar(str[i]);
        else
            ft_putchar('.');
    }
    ft_putchar('\n');
}

static int  ft_print_hex(unsigned char *str, size_t size)
{
    int     i;

    i = -1;
    while (++i < HEX && i < (int)size)
    {
        ft_putatohex(str[i]);
        if (i < HEX - 1 && i < (int)size - 1)
            ft_putchar(' ');
    }
    return (i);
}

static void ft_print_dump_hex(unsigned char *str, size_t size)
{
    int     i;
    int     count;

    i = 0;
    while (i < (int)size)
    {
        ft_puthexaddr((unsigned long long)str + i);
        ft_putstr(" : ");
        count = ft_print_hex(str + i, size + i);
        while (count++ < HEX)
            ft_putchar(' ');
        ft_putstr(" : ");
        ft_print_ascii(str + i, size + i);
        i += HEX;
    }
}

static void ft_display_mem_hex(block_t *block)
{
    while (block) {
        if (block->status == ALLOC)
            ft_print_dump_hex((unsigned char *) block +
        ft_memory_aligning(sizeof(block_t), HEX), block->size);
        block = block->next;
    }
}

void    show_alloc_mem_hex(void)
{
    static char	*zon[3];
    int		i;

    zon[0] = "TINY";
    zon[1] = "SMALL";
    zon[2] = "LARGE";
    i = -1;
    pthread_mutex_lock(&g_mutex);
    while (++i < 3)
    {

        ft_putstr(zon[i]);
        if (g_alloc_map.map[i])
        {
            ft_putendl("\t\t\t\t\t\t\t\tHEX\t\t\t\t\t\t\t\t\tASCII");
            ft_display_mem_hex(g_alloc_map.map[i]);
        }
        else
            ft_putendl(" : NONE");
    }
    pthread_mutex_unlock(&g_mutex);
}
