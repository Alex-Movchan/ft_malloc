/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <amovchan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:07:13 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/14 21:45:39 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void	ft_init_type(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		g_alloc_map.type = TINY;
	else if (size <= (size_t)SMALL_MAX_SIZE)
		g_alloc_map.type = SMALL;
	else
		g_alloc_map.type = LARGE;
}

static void	fr_splitmap(t_block **map, size_t size)
{
	t_block *alloc;

	if ((*map)->size > size && g_alloc_map.type != LARGE)
	{
		alloc = (t_block *)((char *)(*map) + size +
				ft_memory_aligning(sizeof(t_block), HEX));
		alloc->size = (*map)->size - size -
				ft_memory_aligning(sizeof(t_block), HEX);
		alloc->status = FREE;
		alloc->prev = *map;
		if ((*map)->next)
			(*map)->next->prev = alloc;
		alloc->next = (*map)->next;
		(*map)->next = alloc;
		(*map)->size = size;
	}
	(*map)->status = ALLOC;
}

void		ft_env_get_flags(void)
{
	t_alloc_map		*data;
	char			*ptr;

	data = &g_alloc_map;
	if ((ptr = getenv(MALLOC_HISTORY)) && !ft_strcmp(ENABLE, ptr))
	{
		data->flag |= MALLOC_HST;
	}
	if ((ptr = getenv(MALLOC_DEBUG)) && !ft_strcmp(ENABLE, ptr))
		data->flag |= MALLOC_DBG;
	data->flag |= MALLOC_VALID_FLAG;
}

void		*malloc(size_t size)
{
	size_t	aligning_size;
	t_block	*alloc;

	if ((int)size < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	g_alloc_map.flag == MALLOC_UNKNOW_FLAG ? ft_env_get_flags() : 0;
	aligning_size = ft_memory_aligning(size, HEX);
	ft_init_type(aligning_size);
	if (!(alloc = ft_find_place(&g_alloc_map.map[g_alloc_map.type],
			aligning_size)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	fr_splitmap(&alloc, aligning_size);
	pthread_mutex_unlock(&g_mutex);
	g_alloc_map.flag & MALLOC_HST ? ft_pting_hystory(size, alloc) : 0;
	return ((void*)alloc + ft_memory_aligning(sizeof(t_block), HEX));
}
