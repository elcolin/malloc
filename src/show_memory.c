#include "../inc/malloc.h"

extern t_heap *heap_lst;

static void addr_to_str(void *addr)
{
    char    *hexbase = "0123456789ABCDEF";
    char    str[12] = {0};
    unsigned long int   res = (long unsigned int) addr;
    int i = 12;

    while (i--)
    {
        str[i] = hexbase[0xF & res];
        res = res >> 4;
    }
    ft_putstr_fd("0x", 1);
    ft_putstr_fd(str, 1);
}

static void print_block(t_block *first)
{
    while (first)
    {
        addr_to_str((void *) first);
        ft_putstr_fd(" - ", 1);
        addr_to_str((void *) (void *) first + BLOCK_SIZE + first->data_size);
        ft_putstr_fd(" : ", 1);
        ft_putnbr_fd(first->data_size + BLOCK_SIZE, 1);
        ft_putstr_fd(" bytes\n", 1);
        first = first->next;
    }
    
}

static void    print_heap(t_heap *heap)
{
    char *label_str[3] = {"TINY", "SMALL", "LARGE"};
    if (!heap)
        return;
    ft_putstr_fd(label_str[heap->label_size], 1);
    ft_putstr_fd(" : ", 1);
    addr_to_str((void *) heap);
    ft_putstr_fd("\tsize: ", 1);
    ft_putnbr_fd(heap->total_size, 1);
    ft_putstr_fd("\n", 1);
}

void show_alloc_mem()
{
    t_heap *index = heap_lst;
    size_t total_allocated = 0;
    while (index)
    {
        print_heap(index);
        print_block(HEAP_SHIFT(index));
        total_allocated += index->total_size;
        index = index->next;
    }
    ft_putstr_fd("Total : ", 1);
    ft_putnbr_fd(total_allocated, 1);
    ft_putstr_fd(" bytes\n", 1);
}