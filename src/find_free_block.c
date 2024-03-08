#include "../inc/malloc.h"

extern t_heap *heap_lst;

t_block *search_valid_free_block(t_block *first, size_t data_size)
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
            printf("Free block found\n");
            return valid_block;
        }
        get_heap = get_heap->next;
    }
    printf("No free blocks\n");
    return NULL;
}