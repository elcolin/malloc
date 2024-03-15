#ifndef MALLOC_H
# define MALLOC_H

// #include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>


#include <stdio.h>
#include <string.h>


#define HEAP_SHIFT(start) ((void *)start + HEAP_SIZE)
#define BLOCK_SHIFT(start) ((void *)start + BLOCK_SIZE)

#define BLOCK_SIZE (sizeof(t_block))
#define HEAP_SIZE (sizeof(t_heap))

// BLOCK SIZE AND HEAP ALLOCATION
#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)

#define SMALL_HEAP_ALLOCATION_SIZE (16 * getpagesize())
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

// #define LARGE_HEAP_ALLO

typedef enum e_bool{
    FALSE,
    TRUE
} t_bool;

typedef enum e_heap{
    TINY,
    SMALL,
    LARGE
} t_heap_size;

typedef struct s_heap{
    struct s_heap   *prev;
    struct s_heap   *next;
    size_t  total_size;
    size_t  free_size;
    // size_t  block_count;
    t_heap_size label_size;
} t_heap;

typedef struct s_block{
    struct s_block  *prev;
    struct s_block  *next;
    size_t  data_size;
    t_bool    freed;
} t_block;

    // -- mandatory --
void error(t_bool err, char *msg);
void *mmalloc(size_t size);
void ffree(void *ptr);
void show_alloc_mem();
void *rrealloc(void *ptr, size_t size);

    // -- block.c --
t_block *allocate_new_block(t_heap *available_heap, size_t data_size);
void    cut_block(t_block *previous, size_t new_size);
t_block *merge_block(t_block *block_to_merge);

    // -- heap.c --
t_heap *get_last_heap(t_heap *first);
t_heap *allocate_new_heap(size_t heap_size, t_heap_size label);
size_t determine_heap_size(size_t elem_size);
t_heap_size get_heap_label_size(size_t size);

    // -- find.c --
t_block *find_free_block(size_t data_size);
t_block *search_valid_free_block(t_block *first, size_t data_size);
t_heap *find_heap(void *ptr);
t_block *find_block(void *ptr);

    // -- ft_memcpy.c --
void	*ft_memcpy(void *dst, const void *src, size_t n);


#endif