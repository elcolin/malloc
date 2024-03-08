#include "../inc/malloc.h"

extern t_heap *heap_lst;

void print_block(t_block *first)
{
    while (first)
    {
        printf("\t%p - %p: %ld\tisfree: %d\n", (void *) first, (void *) first + first->data_size, first->data_size, first->freed);
        // printf("isfreed: %d", first->freed);
        first = first->next;
    }
    
}

void show_alloc_mem()
{
    char *label_str[3] = {"TINY", "SMALL", "LARGE"};

    t_heap *index = heap_lst;
    while (index)
    {
        printf("%s  :  %p\n", label_str[index->label_size], (void *)index);
        print_block(HEAP_SHIFT(index));
        index = index->next;
    }
}