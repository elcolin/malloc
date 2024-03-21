#include "../inc/malloc.h"

extern t_heap *heap_lst;

static void free_heap(t_heap *heap_to_free)
{
    if (!heap_to_free->prev && heap_to_free->next)
    {//If heap is first
        heap_lst = heap_to_free->next;
        heap_lst->prev = NULL;
    }
    else if (!heap_to_free->next && heap_to_free->prev)
    //If heap is last
        heap_to_free->prev->next = NULL;
    else if (heap_to_free->prev && heap_to_free->next)
    {//If heap is in between two heaps
        heap_to_free->prev->next = heap_to_free->next;
        heap_to_free->next->prev = heap_to_free->prev;
    }
    else if (!heap_to_free->prev && !heap_to_free->next)
    //If heap is alone
        heap_lst = 0;
    munmap(heap_to_free, heap_to_free->total_size);

}

void ffree(void *ptr)
{
    if(!ptr)
        return;
    t_block *block_free = find_block(ptr); //checks if pointer is valid
    if (!block_free)
        return;
    block_free->freed = TRUE;
    if (block_free->prev && block_free->prev->freed == TRUE)
    //If previous block is free
        block_free = merge_block(block_free->prev);
    if (block_free->next && block_free->next->freed == TRUE)
    //If next block is free
        block_free = merge_block(block_free);
    if (!block_free->next && !block_free->prev)
    //If block is alone --> free heap
        return free_heap((t_heap *)((void *)block_free - HEAP_SIZE));
}