#include "../inc/malloc.h"

extern t_heap *heap_lst;

t_block *get_first_block(t_block *block)
{
    if (!block)
        return NULL;
    while (block->prev)
        block = block->prev;
    return block;
}

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
    block_to_merge->data_size += block_to_merge->next->data_size + sizeof(t_block);
    block_to_merge->next = block_to_merge->next->next;
    if (block_to_merge->next)
        block_to_merge->next->prev = block_to_merge;
    return (block_to_merge);
}

t_block *allocate_new_block(t_heap *available_heap, size_t data_size)
{
    t_block *new_block = 0;
    t_block *last_block = get_last_block(HEAP_SHIFT(available_heap));

    if (data_size + sizeof(t_block) > available_heap->free_size)
    {
        printf("/!\\ Heap lacking free space: Available: %ld\tTotal: %ld\n", available_heap->free_size, available_heap->total_size);
        return NULL;
    }
    if (last_block)
    {
        printf("Appending new block\n");
        new_block = BLOCK_SHIFT(last_block) + last_block->data_size;
        new_block->prev = last_block;
        last_block->next = new_block;
    }
    else
    {
        printf("Creating first block\n");
        new_block = HEAP_SHIFT(available_heap);
        new_block->prev = NULL;
    }
    new_block->next = NULL;
    new_block->freed = FALSE;
    // available_heap->block_count++;
    available_heap->free_size -= (data_size + sizeof(t_block));
    new_block->data_size = data_size;
    return new_block;
}