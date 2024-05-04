#include "../inc/malloc.h"

extern t_heap *heap_lst;

size_t determine_heap_size(size_t elem_size)
{
    if (elem_size <= (size_t) TINY_HEAP_ALLOCATION_SIZE / 128)
        return TINY_HEAP_ALLOCATION_SIZE;
    else if (elem_size <= (size_t) SMALL_HEAP_ALLOCATION_SIZE / 128)
        return SMALL_HEAP_ALLOCATION_SIZE;
    return (((HEAP_SIZE + elem_size + BLOCK_SIZE) + getpagesize()) & ~getpagesize());
}

t_heap_size get_heap_label_size(size_t size)
{
    if (size <= (size_t) TINY_HEAP_ALLOCATION_SIZE / 128)
        return TINY;
    else if (size <= (size_t) SMALL_HEAP_ALLOCATION_SIZE / 128)
        return SMALL;
    return LARGE;
}

static t_heap *get_last_heap(t_heap *first)
{
    if (!first)
        return NULL;
    while(first->next)
        first = first->next;
    return first;
}

t_heap  *get_available_heap(size_t wanted_size, t_heap_size heap_label)
{
    t_heap *first = heap_lst;
    while (first)
    {
        if (heap_label == first->label_size && first->free_size >= wanted_size)
            return first;
        first = first->next;
    }
    return NULL;
}

// __uint64_t  get_total_memory_size()
// {
//     t_heap *index = heap_lst;
//     void *last_addr;
//     // __uint64_t  total_size = 0;
//     while (index)
//     {
//         // total_size += index->total_size;
//         if (!index->next)
//             last_addr = (void *)index + index->total_size;
//         index = index->next;
//     }
//     return (__uint64_t)(last_addr - (void*)heap_lst) ;
// }

static t_exec get_system_limit(size_t heap_size)
{
    struct rlimit rlim;
    if (getrlimit(RLIMIT_AS, &rlim) < 0)
        return ERROR;
    // printf("currentlimit: %lld\twanted: %llu\n", rlim.rlim_max , (heap_size) + get_total_memory_size());
    if (rlim.rlim_cur != RLIM_INFINITY && rlim.rlim_cur <= (heap_size) /*+ get_total_memory_size()*/)
        return ERROR;
    return SUCCESS;
}

t_heap *allocate_new_heap(size_t heap_size, t_heap_size label)// go to last heap
{ 
    t_heap *last_heap = get_last_heap(heap_lst);
    t_heap  *new_heap = 0;

    if (get_system_limit(heap_size) == ERROR)
        return (ft_putstr_fd("Memory allocation above system limits.\n", 2), NULL);
    new_heap = (t_heap *)mmap(last_heap, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    // ft_putstr_fd("\n",1);
    if (new_heap == MAP_FAILED) {
        perror("mmap");
        return NULL;
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