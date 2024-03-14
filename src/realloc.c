#include "../inc/malloc.h"

void *rrealloc(void *ptr, size_t size)
{
    if (!ptr)
        return(mmalloc(size));
    t_heap *current_heap = find_heap(ptr);
    t_block *current_block = find_block(ptr);

    if (!current_heap || !current_block)
        return(mmalloc(size));
    if (!size)
    {
        ffree(ptr);
        return (NULL);
    }
    size_t old_size = current_block->data_size;
    printf("heap: %p\t block: %p\n", (void *) current_heap, current_block);
    if (current_block->data_size >= size)
    {
        printf("\tSize below allocation\n");
        cut_block(current_block, size);
        return ptr;
    }
    size_t wanted_size = size - current_block->data_size;
    if (current_block->next && current_block->next->freed == TRUE && current_block->next->data_size + BLOCK_SIZE >= wanted_size)
    {
        printf("\tNext Block is free\n");
        // cut_block(current_block->next, );//fixxxxx
        current_block = merge_block(current_block);
        cut_block(current_block, size);
        return(BLOCK_SHIFT(current_block));
    }
    if (!current_block->next && current_heap && current_heap->free_size >= wanted_size)
    {
        printf("\tFree end of heap\n");
        current_block->data_size += wanted_size;
        current_heap->free_size -= wanted_size;
        return (BLOCK_SHIFT(current_block));
    }
    printf("\tReallocating and copying\n");
    void *new_ptr = 0;
    new_ptr = mmalloc(size);
    new_ptr = ft_memcpy(new_ptr, ptr, old_size);
    ffree(ptr);
    return(new_ptr);
}   

    // t_heap  *current_heap = (t_heap *)((void *)(first) - HEAP_SIZE);
