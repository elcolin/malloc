ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PATH_INC = inc
PATH_OBJ = obj
PATH_SRC = src

SOURCES = block.c find.c free.c heap.c main.c malloc.c realloc.c show_memory.c utils.c
OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc
FLAGS_CC = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)