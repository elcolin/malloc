#include "malloc.h"

// void free(void *ptr){

// }

t_heap *heap = 0;


size_t determine_heap_size(size_t elem_size)
{
    if (elem_size < TINY_BLOCK_SIZE - sizeof(t_block))
        return TINY_HEAP_ALLOCATION_SIZE;
    else if (elem_size < SMALL_BLOCK_SIZE - sizeof(t_block))
        return SMALL_HEAP_ALLOCATION_SIZE;
    return 0;
}

void new_heap(size_t heap_size)
{  
    error(!heap_size, "Block size error");
    printf("here");
    heap = (t_heap *)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
}

void *malloc(size_t size){
    if (!size)
        return NULL;
    size = (size + 15) & ~15;
    // printf("1");
    if (!heap)
        new_heap(determine_heap_size(size));
    return NULL;
}

// void *realloc(void *ptr, size_t size){

// }
