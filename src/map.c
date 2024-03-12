#include "../inc/malloc.h"

extern t_heap *heap_lst;

t_bool is_mapped(void *ptr)
{
    t_heap *index = heap_lst;
    if (!index)
        return FALSE;
    while (index)
    {
        if (HEAP_SHIFT(index) <= ptr && ((void *)index + index->total_size) > ptr)
            return TRUE;
        index = index->next;
    }
    return FALSE;
}

