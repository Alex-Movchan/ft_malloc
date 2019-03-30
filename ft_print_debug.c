#include "ft_malloc.h"



void    ft_pting_hystory(size_t size, t_block *alloc)
{
    unsigned long long  start_address;

    start_address = (unsigned long long int)alloc + ft_memory_aligning(sizeof(t_block), HEX);
    ft_putstr_fd("MALLOC HISTORY: Allocaton size = ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)size, STDERR_FILENO, DEX);
    ft_putstr_fd("; aligning size = ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)alloc->size, STDERR_FILENO, DEX);
    ft_putchar_fd('\n', STDERR_FILENO);
    ft_putstr_fd("MALLOC HISTORY: Allocaton start addres = ", STDERR_FILENO);
    ft_putnbrdase_fd(start_address, STDERR_FILENO, HEX);
    ft_putstr_fd(" finish addres = ", STDERR_FILENO);
    ft_putnbrdase_fd(start_address + alloc->size, STDERR_FILENO, HEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}

void    ft_debug_wrong_ptr(char *ptr)
{
    ft_putstr_fd("MALLOC DEBUG: Wrong pointer ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)ptr, STDERR_FILENO, HEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}

void    ft_print_getmem_dbg(size_t size)
{
    ft_putstr_fd("MALLOC DEBUG: System call: get new memory block size = ", STDERR_FILENO);
    ft_putnbrdase_fd(size, STDERR_FILENO, DEX);
    ft_putstr_fd(" count page = ", STDERR_FILENO);
    ft_putnbrdase_fd(size / getpagesize(), STDERR_FILENO, DEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}

void    ft_print_history_realloc(t_block *alloc, unsigned long long address, size_t size)
{
    ft_putstr_fd("MALLOC HISTORY: Re alloccation poiner:", STDERR_FILENO);
    ft_putnbrdase_fd(address, STDERR_FILENO, HEX);
    ft_putstr_fd(" mem size = ", STDERR_FILENO);
    ft_putnbrdase_fd(alloc->size, STDERR_FILENO, DEX);
    ft_putstr_fd(" new mem size = ", STDERR_FILENO);
    ft_putnbrdase_fd(size, STDERR_FILENO, DEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}

void    ft_ptint_history_free(t_block *block)
{
    ft_putstr_fd("MALLOC HISTORY: Free  obgect ponter = ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)block + ft_memory_aligning(sizeof(t_block), HEX),
            STDERR_FILENO, HEX);
    ft_putstr_fd(" mem size = ", STDERR_FILENO);
    ft_putnbrdase_fd(block->size, STDERR_FILENO, DEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}
void    ft_print_freelarge_dbg(t_block *block)
{
    ft_putstr_fd("MALLOC DEBUG: Free LARGE obgect number of busy pages = ", STDERR_FILENO);
    ft_putnbrdase_fd(block->size / getpagesize(), STDERR_FILENO, DEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}

void    ft_print_join_dbg(t_block *block1, t_block *block2)
{
    size_t	size_head;

    size_head = ft_memory_aligning(sizeof(t_block), HEX);
    ft_putstr_fd("MALLOC DEBUG: Join free block address = ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)block2 + size_head, STDERR_FILENO, HEX);
    ft_putstr_fd(" to block address = ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)block1 + ft_memory_aligning(sizeof(t_block), HEX),
                     STDERR_FILENO, HEX);
    ft_putstr_fd(" new block size = ", STDERR_FILENO);
    ft_putnbrdase_fd((unsigned long long)(block1->size + size_head + block2->size), STDERR_FILENO, DEX);
    ft_putchar_fd('\n', STDERR_FILENO);
}