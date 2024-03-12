#include "../inc/malloc.h"

void *rrealloc(void *ptr, size_t size)
{
    if (!size)
    {
        ffree(ptr);
        return (NULL);
    }
    if (!ptr || is_mapped(ptr) == FALSE)
        return(mmalloc(size));
    t_heap *current_heap = get_heap_from_ptr(ptr);
    t_block *current_block = ptr - BLOCK_SIZE;
    if (!current_block->data_size)
        return(mmalloc(size));
    // t_heap  *current_heap = (t_heap *)((void *)(first) - HEAP_SIZE);
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
        //cut block
        return(BLOCK_SHIFT(merge_block(current_block)));
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