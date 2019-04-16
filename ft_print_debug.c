/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:52:11 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/16 13:55:25 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_debug_wrong_ptr(char *ptr)
{
	ft_putstr_fd("MALLOC DEBUG: Wrong pointer ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)ptr, STDERR_FILENO, HEX);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_print_getmem_dbg(size_t size)
{
	ft_putstr_fd("MALLOC DEBUG: System call: get new memory block size = ",
			STDERR_FILENO);
	ft_putnbrdase_fd(size, STDERR_FILENO, DEX);
	ft_putstr_fd(" count page = ", STDERR_FILENO);
	ft_putnbrdase_fd(size / getpagesize(), STDERR_FILENO, DEX);
}

void	ft_print_freelarge_dbg(t_block *block)
{
	ft_putstr_fd("MALLOC DEBUG: Free LARGE obgect number of busy pages = ",
			STDERR_FILENO);
	ft_putnbrdase_fd(block->size / getpagesize(), STDERR_FILENO, DEX);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_print_join_dbg(t_block *block1, t_block *block2)
{
	size_t	size_head;

	size_head = ft_memory_aligning(sizeof(t_block), HEX);
	ft_putstr_fd("MALLOC DEBUG: Join free block address = ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)block2 + size_head,
			STDERR_FILENO, HEX);
	ft_putstr_fd(" to block address = ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)block1 + ft_memory_aligning(
				sizeof(t_block), HEX), STDERR_FILENO, HEX);
	ft_putstr_fd(" new block size = ", STDERR_FILENO);
	ft_putnbrdase_fd((block1->size + size_head + block2->size),
			STDERR_FILENO, DEX);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_print_memover_dbg(void)
{
	static char	*zon[COUNT_ZONE];

	zon[0] = "TINY";
	zon[1] = "SMALL";
	zon[2] = "LARGE";
	ft_putstr_fd("MALLOC DEBUG: Memory over for zone: ", STDERR_FILENO);
	ft_putendl_fd(zon[g_alloc_map.type], STDERR_FILENO);
}
