/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:55:03 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/16 14:02:46 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	*ft_realocation(t_block *block, void *ptr, size_t size)
{
	void				*new_ptr;
	t_block_type		old_type;

	g_alloc_map.flag & MALLOC_HST ?
	ft_print_history_realloc(block, (unsigned long long)ptr, size) : 0;
	old_type = g_alloc_map.type;
	pthread_mutex_unlock(&g_mutex);
	new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, block->size);
	pthread_mutex_lock(&g_mutex);
	g_alloc_map.type = old_type;
	ft_free_on_map(block);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*alloc;

	if ((int)size < 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_mutex);
	g_alloc_map.flag == MALLOC_UNKNOW_FLAG ? ft_env_get_flags() : 0;
	if (!(alloc = ft_find_in_map(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		g_alloc_map.flag & MALLOC_HST ? ft_debug_wrong_ptr(ptr) : 0;
		return (NULL);
	}
	if (ft_memory_aligning(size, HEX) <= alloc->size)
	{
		pthread_mutex_unlock(&g_mutex);
		g_alloc_map.flag & MALLOC_HST ? ft_pting_hystory(size, alloc) : 0;
		return (ptr);
	}
	return (ft_realocation(alloc, ptr, size));
}
