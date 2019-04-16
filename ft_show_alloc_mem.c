/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:56:17 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/16 15:43:35 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t			ft_print_block_stat(t_block *block)
{
	char	*start;
	char	*end;

	start = (char *)block + ft_memory_aligning(sizeof(t_block), HEX);
	end = (char *)block + block->size + ft_memory_aligning(
			sizeof(t_block), HEX);
	ft_puthexaddr((unsigned long long)start);
	ft_putstr(" - ");
	ft_puthexaddr((unsigned long long)end);
	ft_putstr(" : ");
	ft_putnbr(end - start);
	ft_putendl(" bytes");
	return (end - start);
}

void			t_print_block_stat_dbg(t_block *block)
{
	char	*start;
	char	*end;

	start = (char *)block + ft_memory_aligning(sizeof(t_block), HEX);
	end = (char *)block + block->size + ft_memory_aligning(
			sizeof(t_block), HEX);
	ft_putnbrdase_fd((unsigned long long)start, STDERR_FILENO, HEX);
	ft_putstr_fd(" - ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)end, STDERR_FILENO, HEX);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)(end - start), STDERR_FILENO, DEX);
	ft_putendl_fd(" bytes", STDERR_FILENO);
}

static size_t	ft_display_zone(t_block *block)
{
	size_t	total;

	total = 0;
	while (block)
	{
		if (block->status == ALLOC)
		{
			total += ft_print_block_stat(block);
		}
		else if (g_alloc_map.flag & MALLOC_DBG)
		{
			ft_putstr_fd("MALLOC DEBUG:  Allocated free block ", STDERR_FILENO);
			t_print_block_stat_dbg(block);
		}
		block = block->next;
	}
	return (total);
}

static size_t	ft_display_memmap(t_block *block)
{
	if (!block)
	{
		ft_putendl(" : NONE");
		return (0);
	}
	ft_putstr(" : ");
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

	zon[0] = "TINY";
	zon[1] = "SMALL";
	zon[2] = "LARGE";
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
