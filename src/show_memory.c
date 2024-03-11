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

// void itox(void *ptr)
// {
//     int size = sizeof(ptr) - 1;
//     char    result[9] = {0};
//     char    *hexbase = "0123456789ABCDEF";
//     long long int num = (long long int) ptr;
//     long long int res = 0;

//     printf("size: %d\n", size);
//     while (size >= 0 && num)
//     {
//         res = num % 16;
//         result[size--] = hexbase[res];
//         num = num / 16;
//     }
//     printf("test: 0x%s", result);
//     // for (int i = 0; i < 8; i++)
//     // {
//     //     printf("%c", result[i]);
//     // }
//     printf("\n");
// }

void show_alloc_mem()
{
    char *label_str[3] = {"TINY", "SMALL", "LARGE"};

    t_heap *index = heap_lst;
    while (index)
    {
        printf("%s  :  %p\n", label_str[index->label_size], (void *)index);
        print_block(HEAP_SHIFT(index));
        // itox(HEAP_SHIFT(index));
        index = index->next;
    }
}