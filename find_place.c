#include "ft_malloc.h"

static size_t	ft_getsize(size_t size)
{
	if (g_alloc_map.type == TINY)
		return (ft_memory_aligning(TINY_MAX_SIZE * ALLOCATIONS, (size_t)getpagesize()));
	if (g_alloc_map.type == SMALL)
		return (ft_memory_aligning(SMALL_MAX_SIZE * ALLOCATIONS, (size_t)getpagesize()));
	else
		return (ft_memory_aligning(size, (size_t)getpagesize()));
}

static block_t	*ft_map_place(size_t size, block_t **alloc)
{
	size_t	size_page;
	block_t	*new_block;

	size_page = ft_getsize(size);
	if ((new_block = mmap(0, size_page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->status = FREE;
	new_block->size = size_page - ft_memory_aligning(sizeof(block_t), HEX);
	new_block->next = NULL;
	new_block->prev = *alloc;
	if (*alloc)
		(*alloc)->next = new_block;
	return (new_block);
}

static block_t	*find_free_place(size_t size, block_t **alloc)
{
	block_t	*block;

	block = *alloc;
	while (block && block->next)
	{
		if (block->status == FREE && block->size >= size)
			break ;
		block = block->next;
	}
	return (block);
}

block_t			*ft_find_place(block_t **alloc, size_t size)
{
	block_t	*block;

	if (!*alloc)
		return ((*alloc = ft_map_place(size, alloc)));
	block = find_free_place(size, alloc);
	if (block->status != FREE || block->size < size)
		return (ft_map_place(size, &block));
	else
		return (block);
}

block_t	*ft_find_in_map(void *ptr)
{
	void	*ptr1;
	block_t	*block;
	int		i;

	i = -1;
	ptr1 = ptr - ft_memory_aligning(sizeof(block_t), HEX);
	while (++i < COUNT_ZONE)
	{
		block = g_alloc_map.map[i];
		while (block)
		{
			if ((char*)block == (char*)ptr1)
			{
				g_alloc_map.type = (block_type_t)i;
				return (block);
			}
			block = block->next;
		}
	}
	return (NULL);
}
