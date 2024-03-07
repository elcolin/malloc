#include "malloc.h"

// void free(void *ptr){

// }

t_heap *heap_lst = 0;

size_t determine_heap_size(size_t elem_size)
{
    if (elem_size < TINY_BLOCK_SIZE - sizeof(t_block))
        return TINY_HEAP_ALLOCATION_SIZE;
    else if (elem_size < SMALL_BLOCK_SIZE - sizeof(t_block))
        return SMALL_HEAP_ALLOCATION_SIZE;
    return LARGE_HEAP_ALLOCATION_SIZE;
    // else
        // printf("%ld is above %ld and %ld and %ld\n", elem_size, TINY_BLOCK_SIZE  - sizeof(t_block), SMALL_BLOCK_SIZE  - sizeof(t_block), LARGE_BLOCK_SIZE  - sizeof(t_block));
    // return 0;(elem_size < LARGE_BLOCK_SIZE - sizeof(t_block))
}


t_block *last_block_index(t_block *first)
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

t_heap *last_heap_index(t_heap *first)
{
    // printf("b last heap index: %p\n", first);
    if (!first)
        return NULL;
    while(first->next)
        first = first->next;
    // printf("a last heap index %p\n", first);
    return first;
}


t_block *valid_free_block(t_block *first, size_t data_size)
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

t_block *valid_free_heap(size_t data_size)
{
    t_heap *heap_index = heap_lst;
    t_block *valid_block = 0;
    while (heap_index)
    {
        valid_block = valid_free_block(HEAP_SHIFT(heap_index), data_size);
        if (valid_block)
        {
            printf("Free block found\n");
            return valid_block;
        }
        heap_index = heap_index->next;
    }
    printf("No free blocks\n");
    return NULL;
}

t_block *allocate_new_block(t_heap *available_heap, size_t data_size)
{
    t_block *new_block = 0;
    t_block *last_block = last_block_index(HEAP_SHIFT(available_heap));

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
    available_heap->block_count++;
    available_heap->free_size -= (data_size + sizeof(t_block));
    new_block->data_size = data_size;
    return new_block;
}

t_heap *allocate_new_heap(size_t heap_size)// go to last heap
{  
    t_heap *last_heap = last_heap_index(heap_lst);
    t_heap  *new_heap = 0;

    printf("determined heap size: %ld\n", heap_size);
    new_heap = (t_heap *)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);// handle error
    if (new_heap == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    // printf("%p\n", last_heap);
    printf("new_heap: %p\n", new_heap);
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
    new_heap->block_count = 0;
    new_heap->total_size =  heap_size;
    new_heap->free_size = heap_size - sizeof(t_heap);
    ((t_block *)HEAP_SHIFT(new_heap))->data_size = 0;
    return new_heap;
}

void *mmalloc(size_t size){
    if (!size)
        return NULL;
    // size = (size + 15) & ~15; // to get to the next multiple of 16
    printf("-- Wanted size for new block: %ld\tdatasize: %ld--\n", size + sizeof(t_block), size);
    if (!heap_lst) // If no heap create new heap
        heap_lst = allocate_new_heap(determine_heap_size(size));
    t_block *new_block = valid_free_heap(size);// looking for a block in each heap
    if (!new_block)
    {
        t_heap *last_heap = last_heap_index(heap_lst);
        new_block = allocate_new_block(last_heap, size);
        if (!new_block)
            new_block = allocate_new_block(allocate_new_heap(determine_heap_size(size)), size);
    }
    return BLOCK_SHIFT(new_block);
}