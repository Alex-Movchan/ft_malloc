ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc -Wall -Wextra -Werror -g

PTHREAD = -lpthread

SRC =  tool.c \
        ft_realloc.c \
        ft_puts.c \
        ft_memmove.c \
        ft_malloc.c \
        ft_free.c \
	ft_show_alloc_mem.c \
      	ft_show_alloc_mem_hex.c \
	find_place.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBG)
	@$(CC) -shared -o $@ $(PTHREAD)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"
	@rm -f $(LINK_NAME)
	@ln -s $@ $(LINK_NAME)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Link created" "OK"

%.o: %.c
	$(cc) -shared $(PTHREAD) -c $< -o $

clean:
	@rm -f $(OBJ)


fclean: clean
	rm -f $(LINK_NAME)
	@rm -f $(NAME)

re: fclean all
