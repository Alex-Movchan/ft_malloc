/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:38:24 by amovchan          #+#    #+#             */
/*   Updated: 2019/03/23 19:49:34 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static bool	ft_joinblock(t_block *block1, t_block *block2)
{
	size_t	size_head;

	size_head = ft_memory_aligning(sizeof(t_block), HEX);
	if ((char *)block1 + size_head + block1->size == (char *)block2)
	{
		block1->size += (size_head + block2->size);
		if (block2->next)
			block2->next->prev = block1;
		block1->next = block2->next;
		return (true);
	}
	return (false);
}

void		ft_free_on_map(t_block *block)
{
	if (g_alloc_map.type == LARGE)
	{
		if (block->next)
			block->next->prev = block->prev;
		if (block->prev)
			block->prev->next = block->next;
		if (g_alloc_map.map[LARGE] == block)
			g_alloc_map.map[LARGE] = block->next;
		munmap(block, block->size + ft_memory_aligning(sizeof(t_block), HEX));
		return ;
	}
	block->status = FREE;
	if (block->next && block->next->status == FREE)
		ft_joinblock(block, block->next);
	if (block->prev && block->prev->status == FREE)
		ft_joinblock(block->prev, block);
}

void		free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	if (!(block = ft_find_in_map(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	ft_free_on_map(block);
	pthread_mutex_unlock(&g_mutex);
}
