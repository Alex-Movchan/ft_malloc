/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:40:20 by amovchan          #+#    #+#             */
/*   Updated: 2019/03/23 21:56:35 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>

# define TINY_MAX_SIZE (1 << 11)
# define SMALL_MAX_SIZE (1 << 17)
# define HEX_BASE "0123456789ABCDEF"
# define HEX 16
# define DEX 10
# define ALLOCATIONS 100
# define COUNT_ZONE 3
# define MALLOC_DBG 1 << 3
# define MALLOC_HST 1 << 2
# define MALLOC_UNKNOW_FLAG 0
# define MALLOC_VALID_FLAG 1 << 1
# define MALLOC_HISTORY "MALLOC_HISTORY"
# define MALLOC_DEBUG "MALLOC_DEBUG"
# define ENABLE "1"
# define DISABLE "0"


typedef enum			e_status
{
	FREE = 0,
	ALLOC
}						t_alloc_status;

typedef enum			e_type
{
	TINY = 0,
	SMALL,
	LARGE
}						t_block_type;

typedef struct			s_block
{
	struct s_block		*next;
	struct s_block		*prev;
	size_t				size;
	t_alloc_status		status;
}						t_block;

typedef struct			s_alloc_map
{
	t_block				*map[COUNT_ZONE];
	t_block_type		type;
	char				flag;
}						t_alloc_map;

t_alloc_map				g_alloc_map;
extern pthread_mutex_t	g_mutex;

void					show_alloc_mem(void);
t_block					*ft_find_place(t_block **alloc, size_t size);
size_t					ft_memory_aligning(size_t size, size_t alignment);
t_block					*ft_find_in_map(void *ptr);
void					ft_free_on_map(t_block *block);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
void					*malloc(size_t size);
void					ft_putendl(char const *s);
void					ft_putstr(char const *s);
void					*ft_memmove(void *dst, const void *src, size_t len);
size_t					ft_strlen(char const *s);
void					ft_putnbr(size_t n);
void					ft_puthexaddr(unsigned long long int hex);
void					ft_putchar(char c);
void					show_alloc_mem_hex(void);
int						ft_isprint(int c);
void					ft_putatohex(int c);
void		            ft_env_get_flags(void);
int		                ft_strcmp(const char *s1, const char *s2);
void    ft_putstr_fd(char *msg, int fd);
void    ft_putchar_fd(char c, int fd);
void    ft_putendl_fd(char *msg, int fd);
void    ft_putnbrdase_fd(unsigned long long n, int fd, int base);
void    ft_pting_hystory(size_t size, t_block *alloc);
void    ft_debug_wrong_ptr(char *ptr);
void    ft_print_history_realloc(t_block *alloc, unsigned long long address, size_t size);
void    ft_print_freelarge_dbg(t_block *block);
void    ft_ptint_history_free(t_block *block);
void    ft_print_join_dbg(t_block *block1, t_block *block2);
size_t		ft_print_block_stat(t_block *block);
void    ft_print_getmem_dbg(size_t size);
void		t_print_block_stat_dbg(t_block *block);
void    ft_print_memover_dbg(void);


#endif
