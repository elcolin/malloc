#ifndef MALLOC_H
#define MALLOC_H

#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

#include <stdlib.h>
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

typedef struct s_heap{
    struct s_heap   *prev;
    struct s_heap   *next;
    size_t  total_size;
    size_t  free_size;
    size_t  block_count;
} t_heap;

typedef struct s_block{
    struct s_block  *prev;
    struct s_block  *next;
    size_t  size;
    bool    freed;
} t_block;

#endif