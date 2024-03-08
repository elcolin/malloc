#include "../inc/malloc.h"

extern t_heap *heap_lst;


size_t determine_heap_size(size_t elem_size)
{
    if (elem_size <= TINY_BLOCK_SIZE - sizeof(t_block))
        return TINY_HEAP_ALLOCATION_SIZE;
    else if (elem_size <= SMALL_BLOCK_SIZE - sizeof(t_block))
        return SMALL_HEAP_ALLOCATION_SIZE;
    return (sizeof(t_heap) + elem_size + sizeof(t_block));
}

t_heap_size get_heap_label_size(size_t size)
{
    if (size <= (size_t) TINY_HEAP_ALLOCATION_SIZE)
        return TINY;
    else if (size <= (size_t) SMALL_HEAP_ALLOCATION_SIZE)
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

t_heap *allocate_new_heap(size_t heap_size)// go to last heap
{  
    t_heap *last_heap = get_last_heap(heap_lst);
    t_heap  *new_heap = 0;

    printf("determined heap size: %ld\n", heap_size);
    new_heap = (t_heap *)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);// handle error
    if (new_heap == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    new_heap->label_size = get_heap_label_size(heap_size);
    printf("new_heap: %p %d\n", new_heap, new_heap->label_size);
    new_heap->prev = last_heap;
    if (last_heap)
    {
        printf("~ Appending new heap: %ld ~\n", heap_size);
        last_heap->next = new_heap;
    }
    else
    {
        printf("~ Creating new heap: %ld ~\n", heap_size);
    }
    new_heap->next = NULL;
    // new_heap->block_count = 0;
    new_heap->total_size =  heap_size;
    new_heap->free_size = heap_size - sizeof(t_heap);
    ((t_block *)HEAP_SHIFT(new_heap))->data_size = 0;
    return new_heap;
}