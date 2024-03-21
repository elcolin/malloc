#include "../inc/malloc.h"

t_heap *heap_lst = 0;

void *mmalloc(size_t size){
    if (!size)
        return NULL;
    t_block *new_block = 0;
    size = align4(size);
    if (!heap_lst) // If no heap create new heap
        heap_lst = allocate_new_heap(determine_heap_size(size), get_heap_label_size(size));
    else
        new_block = find_free_block(size);// looking for a block in each heap
    if (!new_block)
    {//If no free blocks suits conditions
        t_heap *last_heap = get_last_heap(heap_lst);
        new_block = allocate_new_block(last_heap, size);
        if (!new_block)//If no space is available at the end of the heap
            new_block = allocate_new_block(allocate_new_heap(determine_heap_size(size), get_heap_label_size(size)), size);
    }
    return BLOCK_SHIFT(new_block);
}