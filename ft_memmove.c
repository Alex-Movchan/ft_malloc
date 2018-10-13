#include "ft_malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	s = (char*)src;
	d = (char*)dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}
void	*ft_memcpy_rev(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	s = (char*)src;
	d = (char*)dst;
	while (n--)
		d[n] = s[n];
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
		ft_memcpy_rev(dst, src, len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
