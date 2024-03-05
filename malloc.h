#ifndef MALLOC_H
# define MALLOC_H

// #include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <stdio.h>
#include <string.h>

#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

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

// typedef enum e_heap{
//     TINY,
//     SMALL,
//     LARGE
// } t_heap_block;

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
    size_t  data_size;
    t_bool    freed;
} t_block;


void error(t_bool err, char *msg);
void *mmalloc(size_t size);

#endif