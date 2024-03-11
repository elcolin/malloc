#include "../inc/malloc.h"

void *rrealloc(void *ptr, size_t size)
{
    if (!size)
    {
        ffree(ptr);
        return (NULL);
    }
    if (!ptr)
        return(mmalloc(size));
    t_block *current_block = ptr - sizeof(t_block);
    t_heap  *current_heap = (t_heap *)((void *)(get_first_block(current_block) - sizeof(t_block)) - sizeof(t_heap));
    if (current_block->data_size >= size)
    {
        printf("\tSize below allocation\n");
        return ptr;
    }
    size_t wanted_size = size - current_block->data_size;
    if (current_block->next && current_block->next->freed == TRUE && current_block->next->data_size + sizeof(t_block) >= wanted_size)
    {
        printf("\tNext Block is free\n");
        return(BLOCK_SHIFT(merge_block(current_block)));
    }
    printf("heap: %p\t block: %p\n", (void *) current_heap, current_block);
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
    new_ptr = ft_memcpy(new_ptr, ptr, size);
    ffree(ptr);
    return(new_ptr);
}   