#include "ft_malloc.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}

void	ft_putnbr(size_t n)
{

	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_puthexaddr(unsigned long long int hex)
{
	if (0 == hex / HEX)
	{
		ft_putstr("0x");
		ft_putchar(HEX_BASE[hex % HEX]);
	}
	else
	{
		ft_puthexaddr(hex / HEX);
		ft_putchar(HEX_BASE[hex % HEX]);
	}
}
