#include "../inc/malloc.h"

#include "time.h"
#include <stdlib.h>
// #include <stdlib.h>
void error(t_bool err, char *msg)
{
    if (err == TRUE)
    {
        write(2, msg, strlen(msg));
        return;
    }
}


int main(){

    char *test[100] = {"100"};
    int i = 100;
    int random;
    srand(time(NULL));
    while (i)
    {
        i--;
        random = rand() % 10 + 1;
        test[i] = mmalloc(random);
        printf("\t-- Allocating i: %d %p--\n", i, test[i]);
        for (int j = 0; j < random; j++)
            test[i][j] = 1;
    }
    i = 100;
    show_alloc_mem();

    while (i)
    {
        i--;
        printf("\t-- Freeing i: %d %p --\n", i, test[i]);
        // if (i != 2 && i !=8 && i!= 49 && i!= 9)
            ffree(test[i]);
    }
    show_alloc_mem();
    i = 100;
     while (i)
    {
        i--;
        random = rand() % 100;
        printf("\t-- reallocating i: %d %p for size %d --\n", i, BLOCK_SHIFT(test[i]), random);
        test[i] = rrealloc(test[i], random);
        // show_alloc_mem();
        for (int j = 0; j < random; j++)
            test[i][j] = 0;
    }
    i=25;
    while (i)
    {
        i--;
        printf("\t-- Freeing i: %d %p --\n", i, test[i]);
        // if (i != 2 && i !=8 && i!= 49 && i!= 9)
            ffree(test[i]);
    }
    i = 75;
     while (i)
    {
        i--;
        random = rand() % 1000;
        printf("\t-- reallocating i: %d %p for size %d--\n", i, BLOCK_SHIFT(test[i]), random);
        test[i] = rrealloc(test[i], random);
        // show_alloc_mem();
        for (int j = 0; j < random; j++)
            test[i][j] = 0;
    }
    i=100;
    show_alloc_mem();
    while (i)
    {
        i--;
        printf("Freeing i: %d %p\n", i, test[i]);
        // if (i != 2 && i !=8 && i!= 49 && i!= 9)
            ffree(test[i]);
    }
    show_alloc_mem();

}

    // i = 2100;
    // while (i < 1000)
    // {
    //     printf("Freeing i: %d %p\n", i, test[i]);
    //     if (i != 2 && i !=8 && i!= 49 && i!= 9)
    //         ffree(test[i]);
    //     i++;
    // }
    // i = 99;
    //  while (i)
    // {
    //     random = rand() % 100;
    //     printf("\t-- reallocating i: %d for size %d--\n", i, random);
    //     test[i] = rrealloc(test[i], random);
    //     for (int j = 0; j < random; j++)
    //         test[i][j] = 0;
    //     i--;
    // }
    // i = 100;
    //  while (i)
    // {
    //     i--;
    //     printf("Freeing i: %d\n", i);
    //         ffree(test[i]);
    // }
    // show_alloc_mem();