#include "../inc/malloc.h"

extern t_heap *heap_lst;

static t_block *search_valid_free_block(t_block *first, size_t data_size)
{
    if (!first)
        return NULL;
    while (first)
    {
        if (first->freed == TRUE && first->data_size >= data_size)
            return first;
        first = first->next;
    }
    return NULL;
}

t_block *find_free_block(size_t data_size)
{
    t_heap *get_heap = heap_lst;
    t_block *valid_block = 0;
    while (get_heap)
    {
        valid_block = search_valid_free_block(HEAP_SHIFT(get_heap), data_size);
        if (valid_block)
        {
            //printf("Free block found: datasize: %ld\t addr: %p\n", valid_block->data_size, (void *)valid_block);
            valid_block->freed = FALSE;
            cut_block(valid_block, data_size);
            return valid_block;
        }
        get_heap = get_heap->next;
    }
    return NULL;
}

t_block *find_block(void *ptr)
{
    t_heap *current_heap = find_heap(ptr);
    if (!ptr || !current_heap)
        return NULL;
    t_block *index = HEAP_SHIFT(current_heap);
    while (index)
    {
        if (ptr == BLOCK_SHIFT(index))
            return index;
        index = index->next;
    }
    return NULL;
}

t_heap *find_heap(void *ptr)
{
    t_heap *index = heap_lst;
    if (!ptr || !index)
        return NULL;
    while (index)
    {
        // //printf("hereheap");
        if (HEAP_SHIFT(index) <= ptr && ((void *)index + index->total_size) > ptr)
            return index;
        index = index->next;
    }
    return NULL;
}

