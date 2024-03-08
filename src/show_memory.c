#include "../inc/malloc.h"

extern t_heap *heap_lst;

void show_alloc_mem()
{
    char *label_str[3] = {"TINY", "SMALL", "LARGE"};

    t_heap *index = heap_lst;
    while (index)
    {
        printf("%s  :  %p\n", label_str[index->label_size], (void *)index);
        index = index->next;
    }
}