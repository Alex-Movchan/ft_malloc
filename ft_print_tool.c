#include "ft_malloc.h"

void    ft_putstr_fd(char *msg, int fd)
{
    write(fd, msg, ft_strlen(msg));
}

void    ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void    ft_putendl_fd(char *msg, int fd)
{
    ft_putstr_fd(msg, fd);
    ft_putchar_fd('\n',fd);
}

void    ft_putnbrdase_fd(unsigned long long n, int fd, int base)
{

    if (n / base == 0)
    {
        if (base == HEX)
            ft_putstr_fd("0x", fd);;
        ft_putchar_fd(HEX_BASE[n%base], fd);
    }
    else
    {
        ft_putnbrdase_fd(n / (unsigned long long)base, fd, base);
        ft_putchar_fd(HEX_BASE[n%base], fd);
    }
}
