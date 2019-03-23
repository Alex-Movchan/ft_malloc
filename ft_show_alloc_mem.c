/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:56:17 by amovchan          #+#    #+#             */
/*   Updated: 2019/03/23 19:57:41 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t	ft_display_zone(t_block *block)
{
	size_t	total;
	char	*start;
	char	*end;

	total = 0;
	while (block)
	{
		if (block->status == ALLOC)
		{
			start = (char *)block + ft_memory_aligning(sizeof(t_block), HEX);
			end = (char *)block + block->size + ft_memory_aligning(
				sizeof(t_block), HEX);
			ft_puthexaddr((unsigned long long)start);
			ft_putstr(" - ");
			ft_puthexaddr((unsigned long long)end);
			ft_putstr(" : ");
			ft_putnbr(end - start);
			ft_putendl(" bytes");
			total += (end - start);
		}
		block = block->next;
	}
	return (total);
}

static size_t	ft_display_memmap(t_block *block)
{
	if (!block)
	{
		ft_putendl("NONE");
		return (0);
	}
	ft_puthexaddr((unsigned long long)block);
	ft_putchar('\n');
	while (block->prev)
		block = block->prev;
	return (ft_display_zone(block));
}

void			show_alloc_mem(void)
{
	static char	*zon[COUNT_ZONE];
	size_t		total;
	int			i;

	zon[0] = "TINY : ";
	zon[1] = "SMALL : ";
	zon[2] = "LARGE : ";
	i = -1;
	total = 0;
	pthread_mutex_lock(&g_mutex);
	while (++i < COUNT_ZONE)
	{
		ft_putstr(zon[i]);
		total += ft_display_memmap(g_alloc_map.map[i]);
	}
	pthread_mutex_unlock(&g_mutex);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" bytes");
}
