#include "malloc.h"


void ffree(void *ptr)
{
    t_block *block_free = ptr - sizeof(t_block);
    block_free->freed = TRUE;

    printf("! Freed Block: %ld !\n", block_free->data_size);
    if (block_free->prev && block_free->prev->freed == TRUE)
        block_free->prev->next = block_free->next;
    else if (block_free->next && block_free->next->freed == TRUE)
        block_free->next = block_free->next->next;
}