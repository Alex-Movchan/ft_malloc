#include "ft_malloc.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_memory_aligning(size_t size, size_t alignment)
{
	if (size == 0)
		return (alignment);
	else
		return ((size - 1) / alignment * alignment + alignment);
}