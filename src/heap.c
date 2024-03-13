#include "../inc/malloc.h"

extern t_heap *heap_lst;

size_t determine_heap_size(size_t elem_size)
{
    if (elem_size <= TINY_BLOCK_SIZE - BLOCK_SIZE)
        return TINY_HEAP_ALLOCATION_SIZE;
    else if (elem_size <= SMALL_BLOCK_SIZE - BLOCK_SIZE)
        return SMALL_HEAP_ALLOCATION_SIZE;
    return (HEAP_SIZE + elem_size + BLOCK_SIZE);
}

t_heap_size get_heap_label_size(size_t size)
{
    if (size <= (size_t) TINY_BLOCK_SIZE - BLOCK_SIZE)
        return TINY;
    else if (size <= (size_t) SMALL_BLOCK_SIZE - BLOCK_SIZE)
        return SMALL;
    return LARGE;
}

t_heap *get_last_heap(t_heap *first)
{
    if (!first)
        return NULL;
    while(first->next)
        first = first->next;
    return first;
}

t_heap *allocate_new_heap(size_t heap_size, t_heap_size label)// go to last heap
{  
    t_heap *last_heap = get_last_heap(heap_lst);
    t_heap  *new_heap = 0;

    // printf("determined heap size: %ld\n", heap_size);
    new_heap = (t_heap *)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);// handle error
    if (new_heap == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    new_heap->label_size = label;
    new_heap->prev = last_heap;
    if (last_heap)
        last_heap->next = new_heap;
    new_heap->next = NULL;
    new_heap->total_size =  heap_size;
    new_heap->free_size = heap_size - HEAP_SIZE;
    ((t_block *)HEAP_SHIFT(new_heap))->data_size = 0;
    return new_heap;
}
    // printf("new_heap: %p %d\n", new_heap, new_heap->label_size);
//  if (last_heap)
//     {
//         printf("~ Appending new heap: %ld ~\n", heap_size);
//         last_heap->next = new_heap;
//     }
//     else
//     {
//         printf("~ Creating new heap: %ld ~\n", heap_size);
//     }