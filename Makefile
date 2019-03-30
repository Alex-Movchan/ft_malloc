
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_LINK = libft_malloc.so
NAME = libft_malloc_$(HOSTTYPE).so

CFLAGS = -fPIC -pthread -g -Wall -Wextra -Werror
CC = gcc

PTHREAD = -lpthread

SRCS = ft_realloc.c \
	ft_puts.c \
	ft_memmove.c \
	ft_malloc.c \
	ft_free.c \
	tools.c \
	ft_show_alloc_mem.c \
	ft_show_alloc_mem_hex.c \
	find_place.c \
	ft_print_tool.c \
	ft_print_debug.c

OBJ = ft_realloc.o \
	ft_puts.o \
	ft_memmove.o \
	ft_malloc.o \
	ft_free.o \
	tools.o \
	ft_show_alloc_mem.o \
	ft_show_alloc_mem_hex.o \
	find_place.o \
	ft_print_tool.o \
	ft_print_debug.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -g -o $@ $(OBJ)
	ln -sf $(NAME) $(NAME_LINK)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(PRGFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_LINK)

re: fclean all
