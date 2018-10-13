
#ifndef FT_MALLOC_H
#define FT_MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <pthread.h>

# define TINY_MAX_SIZE 352
# define SMALL_MAX_SIZE 4064
# define STANDART_MEMORY_ALIGNING 16
# define HEX_BASE "0123456789ABCDEF"
# define HEX 16

typedef enum			s_status
{
	FREE = 0,
	ALLOC
}						alloc_status_t;

typedef enum			s_type
{
	TINY = 0,
	SMALL,
	LARGE
}						block_type_t;

typedef struct			s_block
{
	struct s_block		*next;
	struct s_block		*prev;
	size_t				size;
	alloc_status_t		status;
}						block_t;

typedef struct			s_alloc_map
{
	block_t				*map[3];
	block_type_t		type;
//	bool				init;
}						alloc_map_t;

alloc_map_t				g_alloc_map;
extern pthread_mutex_t	g_mutex;

block_t					*ft_find_place(block_t **alloc, size_t size);
size_t					ft_memory_aligning(size_t size, size_t alignment);
block_t					*ft_find_in_map(void *ptr);
void					ft_free_on_map(block_t *block);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
void					*malloc(size_t size);
void					ft_putendl(char const *s);
void					ft_putstr(char const *s);
void					*ft_memmove(void *dst, const void *src, size_t len);
size_t					ft_strlen(char const *s);
void					ft_putnbr(size_t n);
void					ft_puthex(unsigned long long int hex);
void					ft_putchar(char c);
void					show_alloc_mem(void);

#endif
