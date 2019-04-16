/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:48:15 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/16 13:51:38 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_pting_hystory(size_t size, t_block *alloc)
{
	unsigned long long	start_address;

	start_address = (unsigned long long int)alloc +
		ft_memory_aligning(sizeof(t_block), HEX);
	ft_putstr_fd("MALLOC HISTORY: Allocaton size = ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)size, STDERR_FILENO, DEX);
	ft_putstr_fd("; aligning size = ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)alloc->size, STDERR_FILENO, DEX);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putstr_fd("MALLOC HISTORY: Allocaton start addres = ",
			STDERR_FILENO);
	ft_putnbrdase_fd(start_address, STDERR_FILENO, HEX);
	ft_putstr_fd(" finish addres = ", STDERR_FILENO);
	ft_putnbrdase_fd(start_address + alloc->size, STDERR_FILENO, HEX);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_print_history_realloc(t_block *alloc,
		unsigned long long address, size_t size)
{
	ft_putstr_fd("MALLOC HISTORY: Re alloccation poiner:",
			STDERR_FILENO);
	ft_putnbrdase_fd(address, STDERR_FILENO, HEX);
	ft_putstr_fd(" mem size = ", STDERR_FILENO);
	ft_putnbrdase_fd(alloc->size, STDERR_FILENO, DEX);
	ft_putstr_fd(" new mem size = ", STDERR_FILENO);
	ft_putnbrdase_fd(size, STDERR_FILENO, DEX);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_ptint_history_free(t_block *block)
{
	ft_putstr_fd("MALLOC HISTORY: Free  obgect ponter = ", STDERR_FILENO);
	ft_putnbrdase_fd((unsigned long long)block +
			ft_memory_aligning(sizeof(t_block), HEX),
				STDERR_FILENO, HEX);
	ft_putstr_fd(" mem size = ", STDERR_FILENO);
	ft_putnbrdase_fd(block->size, STDERR_FILENO, DEX);
	ft_putchar_fd('\n', STDERR_FILENO);
}
