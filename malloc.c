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
    heap = (t_heap *)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    heap->prev = NULL;
    heap->next = NULL;
    heap->block_count = 0;
    heap->total_size =  heap_size - sizeof(t_heap);
    heap->free_size = heap_size - sizeof(t_heap);

}

t_block *last_block_index(t_block *first)
{
    while(first->next)
        first = first->next;
    return first;
}

t_block *valid_free_block(t_block *first, size_t size)
{
    while (first->next)
    {
        if (first->freed == TRUE && first->data_size >= size)
            return first;
        first = first->next;
    }
    return NULL;
}

void *new_block(size_t block_size)
{
    t_block *first_block = (t_block *)HEAP_SHIFT((void *)heap);
    t_block *new_block = NULL;
    if (heap->block_count)
    {
        new_block = valid_free_block(first_block, block_size);
        if (!new_block)//verifier si fin de heap et gestion
        {
            new_block = last_block_index(first_block);
            heap->block_count++;
        }
    }
    else
    {
        new_block = first_block;
        heap->block_count++;
    }
    new_block->data_size = block_size;
    new_block->next = (t_block *)BLOCK_SHIFT(new_block) + block_size;
    new_block->next->prev = new_block;
    heap->free_size -= (sizeof(t_block) + block_size);
    printf("Heap state:\nBlock Size: %ld\tBlock count: %ld\tTotal Size: %ld\tFree Size: %ld\n",sizeof(t_block) ,heap->block_count, heap->total_size, heap->free_size);
    return (BLOCK_SHIFT(new_block));

}

void *mmalloc(size_t size){
    if (!size)
        return NULL;
    // size = (size + 15) & ~15;
    if (!heap) // size > freesize
        new_heap(determine_heap_size(size));
    // printf("Heap state:\nBlock count: %ld\tTotal Size: %ld\tFree Size: %ld\n", heap->block_count, heap->total_size, heap->free_size);
    return new_block(size);
}

// void *realloc(void *ptr, size_t size){

// }
