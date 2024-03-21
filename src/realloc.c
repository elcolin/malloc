#include "../inc/malloc.h"

void *rrealloc(void *ptr, size_t size)
{
    if (!ptr)
        return(mmalloc(size));

    t_heap *current_heap = find_heap(ptr);
    t_block *current_block = find_block(ptr);

    if (!current_heap || !current_block)
    //Heap isn't allocated or address isn't valid
        return(mmalloc(size));
    if (!size)
    //Size is null and address valid, freeing address
        return (ffree(ptr), NULL);
    size = align4(size);
    if (current_block->data_size >= size)
    //Size is below allocation
        return (cut_block(current_block, size), ptr);
            
    size_t size_to_add = size - current_block->data_size;
    if (current_block->next && current_block->next->freed == TRUE && current_block->next->data_size + BLOCK_SIZE >= size_to_add)
    {//Next Block is free
        current_block = merge_block(current_block);
        return(cut_block(current_block, size), BLOCK_SHIFT(current_block));
    }
    if (!current_block->next && current_heap && current_heap->free_size >= size_to_add)
    {//End of heap is free
        current_block->data_size += size_to_add;
        current_heap->free_size -= size_to_add;
        return (BLOCK_SHIFT(current_block));
    }
    void *new_ptr = 0;
    size_t old_size = current_block->data_size;

    new_ptr = mmalloc(size);
    new_ptr = ft_memcpy(new_ptr, ptr, old_size);
    ffree(ptr);
    return(new_ptr);
}   

    // t_heap  *current_heap = (t_heap *)((void *)(first) - HEAP_SIZE);
