ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PATH_INC = inc
PATH_OBJ = obj
PATH_SRC = src

SOURCES = block.c find.c free.c heap.c malloc.c realloc.c show_memory.c utils.c
OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc
FLAGS_CC = -Wall -Wextra -Werror -fPIC 
FLAGS_LIB = -shared

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -fsanitize=address -g3 $(FLAGS_LIB) -o $@ $(OBJECTS)
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)
	@echo "Make done"

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(FLAGS_CC) $^ -O0 -g -I $(PATH_INC) -fsanitize=address  -g3

clean:
	@rm -rf $(PATH_OBJ)
	@echo "Clean done"

fclean: clean
	@rm -f $(NAME) $(LIB_NAME)
	@echo "Fclean done"

re: fclean $(NAME)