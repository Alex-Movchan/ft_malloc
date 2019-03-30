/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:05:15 by amovchan          #+#    #+#             */
/*   Updated: 2019/03/23 20:05:38 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}

int		ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

void	ft_putatohex(int c)
{
	ft_putchar(HEX_BASE[c / HEX]);
	ft_putchar(HEX_BASE[c % HEX]);
}
