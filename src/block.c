#include "../inc/malloc.h"

extern t_heap *heap_lst;

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
    if (!block_to_merge || !block_to_merge->next)
        return block_to_merge;
    block_to_merge->data_size += block_to_merge->next->data_size + BLOCK_SIZE;
    block_to_merge->next = block_to_merge->next->next;
    block_to_merge->next->prev = block_to_merge;
    return (block_to_merge);
}

void    cut_block(t_block *block_to_cut, size_t new_size)
{
    t_block *new_block = 0;
    if (!new_size || !block_to_cut)
        return;
    if ((block_to_cut->data_size - new_size < BLOCK_SIZE))
        return;

    new_block = BLOCK_SHIFT(block_to_cut) + new_size;
    new_block->freed = TRUE;
    new_block->data_size = block_to_cut->data_size - new_size - BLOCK_SIZE;
    block_to_cut->data_size = new_size;

    new_block->prev = block_to_cut;
    new_block->next = block_to_cut->next;
    block_to_cut->next = new_block;
    if (new_block->next)
    {
        new_block->next->prev = new_block;
        if (new_block->next->freed == TRUE)
           merge_block(new_block);
    }
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
    available_heap->free_size -= (data_size + BLOCK_SIZE);
    new_block->data_size = data_size;
    return new_block;
}