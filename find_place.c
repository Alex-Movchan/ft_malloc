/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_place.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:29:18 by amovchan          #+#    #+#             */
/*   Updated: 2019/03/31 01:59:56 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t	ft_getsize(size_t size)
{
	if (g_alloc_map.type == TINY)
	{
		return (ft_memory_aligning(TINY_MAX_SIZE * ALLOCATIONS,
		(size_t)getpagesize()));
	}
	if (g_alloc_map.type == SMALL)
	{
		return (ft_memory_aligning(SMALL_MAX_SIZE * ALLOCATIONS,
			(size_t)getpagesize()));
	}
	else
		return (ft_memory_aligning(size, (size_t)getpagesize()));
}

static t_block	*ft_map_place(size_t size, t_block **alloc)
{
	size_t	size_page;
	t_block	*new_block;

	size_page = ft_getsize(size);
	g_alloc_map.flag & MALLOC_DBG ? ft_print_getmem_dbg(size_page) : 0;
	if ((new_block = mmap(0, size_page, PROT_READ | PROT_WRITE, MAP_ANON |
					MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		g_alloc_map.flag & MALLOC_DBG ? ft_putendl_fd(" FAILURE", STDERR_FILENO) : 0;
		return (NULL);
	}
	g_alloc_map.flag & MALLOC_DBG ? ft_putendl_fd(" SUCCESS", STDERR_FILENO) : 0;
	new_block->status = FREE;
	new_block->size = size_page - ft_memory_aligning(sizeof(t_block), HEX);
	new_block->next = NULL;
	new_block->prev = *alloc;
	if (*alloc)
		(*alloc)->next = new_block;
	return (new_block);
}

static t_block	*find_free_place(size_t size, t_block **alloc)
{
	t_block	*block;

	block = *alloc;
	while (block && block->next)
	{
		if (block->status == FREE && block->size >= size)
			break ;
		block = block->next;
	}
	return (block);
}

t_block			*ft_find_place(t_block **alloc, size_t size)
{
	t_block	*block;

	if (!*alloc)
		return ((*alloc = ft_map_place(size, alloc)));

	block = find_free_place(size, alloc);
	if (block->status != FREE || block->size < size)
	{
		g_alloc_map.flag & MALLOC_DBG ? ft_print_memover_dbg() : 0;
		return (ft_map_place(size, &block));
	}
	else
		return (block);
}

t_block			*ft_find_in_map(void *ptr)
{
	void	*ptr1;
	t_block	*block;
	int		i;

	i = -1;
	ptr1 = ptr - ft_memory_aligning(sizeof(t_block), HEX);
	while (++i < COUNT_ZONE)
	{
		block = g_alloc_map.map[i];
		while (block)
		{
			if ((char*)block == (char*)ptr1)
			{
				g_alloc_map.type = (t_block_type)i;
				return (block);
			}
			block = block->next;
		}
	}
	return (NULL);
}
