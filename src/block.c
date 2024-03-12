#include "../inc/malloc.h"

extern t_heap *heap_lst;

// t_block *get_first_block(t_block *block)
// {
//     // if (!block || !block->data_size)
//     //     return NULL;
//     // while (block->prev)
//     //     block = block->prev;
//     // return block;
// }

t_block *get_last_block(t_block *first)
{
    t_block *index = first;
    if (!index)
        return NULL;
    while(index->next)
        index = index->next;
    if (index == first && !first->data_size)
        return NULL;
    return index;
}

t_block *merge_block(t_block *block_to_merge)
{
    block_to_merge->data_size += block_to_merge->next->data_size + BLOCK_SIZE;
    block_to_merge->next = block_to_merge->next->next;
    if (block_to_merge->next)
        block_to_merge->next->prev = block_to_merge;
    return (block_to_merge);
}

void    cut_block(t_block *previous, size_t new_size)
{
    t_block *new_block = 0;
    if (!new_size)
        return;
    if (!(previous->data_size - new_size > BLOCK_SIZE))
        return;
    new_block = BLOCK_SHIFT(previous) + new_size;
    new_block->prev = previous;
    new_block->next = previous->next;
    new_block->prev->next = new_block;
    new_block->freed = TRUE;
    new_block->data_size = previous->data_size - new_size - BLOCK_SIZE;
    previous->data_size = new_size;
    if (new_block->next)
        new_block->next->prev = new_block;
}

t_block *allocate_new_block(t_heap *available_heap, size_t data_size)
{
    t_block *new_block = 0;
    t_block *last_block = get_last_block(HEAP_SHIFT(available_heap));

    if (data_size + BLOCK_SIZE > available_heap->free_size)
    {
        printf("/!\\ Heap lacking free space: Available: %ld\tTotal: %ld\n", available_heap->free_size, available_heap->total_size);
        return NULL;
    }
    if (last_block)
    {
        new_block = BLOCK_SHIFT(last_block) + last_block->data_size;
        new_block->prev = last_block;
        last_block->next = new_block;
        printf("Appending new block at %p\n", new_block);

    }
    else
    {
        new_block = HEAP_SHIFT(available_heap);
        printf("Creating first block: %p\n", new_block);
        new_block->prev = NULL;
    }
    new_block->next = NULL;
    new_block->freed = FALSE;
    // available_heap->block_count++;
    available_heap->free_size -= (data_size + BLOCK_SIZE);
    new_block->data_size = data_size;
    return new_block;
}