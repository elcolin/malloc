#include "../inc/malloc.h"

#include "time.h"
#include <stdlib.h>

int main()
{
    char *test[100] = {0};

    int random;
    int max_mem = 2000;
    srand(time(NULL));
    
    for (int i = 0; i < 100; i++)
    {
        random = rand() % 100;
        if (!test[random])
            test[random] = mmalloc(rand() % max_mem);
    }
    show_alloc_mem();
    for (int i = 0; i < 100; i++)
    {
        random = rand() % 100;
        test[random] = rrealloc(test[random], rand() % max_mem);
    }
    show_alloc_mem();
    for (int i = 0; i < 100; i++)
    {
        ffree(test[i]);
    }
    show_alloc_mem();
}