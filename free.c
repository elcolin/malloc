#include "malloc.h"

extern t_heap *heap_lst;

void free_heap(t_heap *heap_to_free)
{
    printf("Trying to free heap: %p\n", heap_to_free);
    if (!heap_to_free->prev && heap_to_free->next)
    {
        heap_lst = heap_to_free->next;
        heap_lst->prev = NULL;
    }
    else if (!heap_to_free->next && heap_to_free->prev)
        heap_to_free->prev->next = NULL;
    else if (heap_to_free->prev && heap_to_free->next)
    {
        heap_to_free->prev->next = heap_to_free->next;
        heap_to_free->next->prev = heap_to_free->prev;
    }
    else if (!heap_to_free->prev && !heap_to_free->next)
        heap_lst = 0;
    munmap(heap_to_free, heap_to_free->total_size);

}

void ffree(void *ptr)
{
    if(!ptr)
        return;
    t_block *block_free = ptr - sizeof(t_block);
    block_free->freed = TRUE;

    printf("! Freed Block: %ld %p!\n", block_free->data_size, block_free);
    if (block_free->prev && block_free->prev->freed == TRUE)
    {
        printf("prev exists %p\n", block_free->prev);
        block_free->prev->data_size += block_free->data_size + sizeof(t_block);
        block_free->prev->next = block_free->next;
        if (block_free->next)
            block_free->next->prev = block_free->prev;
        block_free = block_free->prev;
    }
    if (block_free->next && block_free->next->freed == TRUE)
    {
        printf("next exists %p\n", block_free->next);
        block_free->data_size += block_free->next->data_size + sizeof(t_block);
        block_free->next = block_free->next->next;
        block_free->next->prev = block_free;

    }
    if (!block_free->next && !block_free->prev)
    {
        printf("neither exists\n");
        // munmap(heap_lst, heap_lst->total_size);
        // printf("Trying to free heap: %p\n",);
        free_heap((t_heap *)((void *)block_free - sizeof(t_heap)));
    }
}