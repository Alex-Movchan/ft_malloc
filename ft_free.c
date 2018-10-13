#include "ft_malloc.h"

static void	ft_joinblock(block_t *block1, block_t *block2)
{
	size_t	size_head;

	size_head = ft_memory_aligning(sizeof(block_t), STANDART_MEMORY_ALIGNING);
	if ((char *)block1 + size_head + block1->size == (char *)block2)
	{
		block1->size += (size_head + block2->size);
		if (block2->next)
			block2->next->prev = block1;
		block1->next = block2->next;
	}
}

void	ft_free_on_map(block_t *block)
{
	block->status = FREE;
	if (block->next && block->next->status == FREE)
		ft_joinblock(block, block->next);
	if (block->prev && block->prev->status == FREE)
		ft_joinblock(block->prev, block);
}

void	free(void *ptr)
{
	block_t	*block;

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