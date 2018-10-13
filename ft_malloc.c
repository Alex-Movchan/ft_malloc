#include "ft_malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void	ft_init_type(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		g_alloc_map.type = TINY;
	else if (size <= SMALL_MAX_SIZE)
		g_alloc_map.type = SMALL;
	else
		g_alloc_map.type = LARGE;
}

static void	fr_splitmap(block_t **map, size_t size)
{
	block_t	*alloc;

	alloc = (block_t*)((char*)(*map) + size + ft_memory_aligning(sizeof(block_t), STANDART_MEMORY_ALIGNING));
	alloc->size = (*map)->size - size - ft_memory_aligning(sizeof(block_t), STANDART_MEMORY_ALIGNING);
	alloc->status = FREE;
	alloc->prev = *map;
	if ((*map)->next)
		(*map)->next->prev = alloc;
	alloc->next = (*map)->next;
	(*map)->next = alloc;
	(*map)->size = size;
}

void		*malloc(size_t size)
{
	size_t	aligning_size;
	block_t	*alloc;

	if ((int)size < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	aligning_size = ft_memory_aligning(size, STANDART_MEMORY_ALIGNING);
	ft_init_type(aligning_size);
	if (!(alloc = ft_find_place(&g_alloc_map.map[g_alloc_map.type], aligning_size)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (alloc->size > aligning_size)
		fr_splitmap(&alloc, aligning_size);
	alloc->status = ALLOC;
	pthread_mutex_unlock(&g_mutex);
	return ((void*)alloc + ft_memory_aligning(sizeof(block_t), STANDART_MEMORY_ALIGNING));
}