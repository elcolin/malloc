#include "../inc/malloc.h"

#include "time.h"
#include <stdlib.h>

int main()
{
    char *test[100] = {0};

    int random = 0;
    int max_mem = rand() % 20000;
    srand(time(NULL));
    int j = 0;

    
    for (int i = 0; i < 100; i++)
    {
        random = rand() % 100;
        if (!test[random])
        {
            test[random] = mmalloc(j = rand() % max_mem);
            while (j)
            {
                j--;
                test[random][j] = 'a';
            }
        }
    }
    show_alloc_mem();
    max_mem = rand() % 200;
    for (int i = 0; i < 100; i++)
    {
        random = rand() % 100;
        test[random] = rrealloc(test[random], j = rand() % max_mem);
        if (j)
        {
            // ft_putnbr_fd(j, 2);
            // ft_putstr_fd("\n", 2);
            test[random][--j] = '\0';
        }
        while (j)
        {
            j--;
            test[random][j] = 'a';
        }
        if (test[random])
            printf("%s\n", test[random]);
    }
    show_alloc_mem();
    for (int i = 0; i < 100; i++)
    {
        ffree(test[i]);
    }
    show_alloc_mem();
}