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

    char *test[100];
    int i = 0;
    int random;
    srand(time(NULL));
    while (i < 100)
    {
        printf("\t-- Allocating i: %d --\n", i);
        random = rand() % 1000 + 1;
        test[i] = mmalloc(random);
        for (int j = 0; j < random; j++)
            test[i][j] = 1;
        i++;
    }
    i = 0;
    // while (i < 50)
    // {
    //     printf("Freeing i: %d\n", i);
    //     ffree(test[i]);
    //     i++;
    // }
    i = 50;
    // while (i < 100)
    // {
    //     random = rand() % 10 + 1;
    //     printf("\t-- reallocating i: %d for size %d--\n", i, random);
    //     test[i] = rrealloc(test[i], random);
    //     for (int j = 0; j < random; j++)
    //         test[i][j] = 0;
    //     i++;
    // }
    i = 25;
    // ffree(test[2]);
    // ffree(test[8]);
    // ffree(test[49]);
    // ffree(test[9]);
    while (i < 50)
    {
        printf("Freeing i: %d\n", i);
        if (i != 2 && i !=8 && i!= 49 && i!= 9)
            ffree(test[i]);
        i++;
    }
    i = 25;
     while (i < 50)
    {
        random = rand() % 10 + 1;
        printf("\t-- reallocating i: %d for size %d--\n", i, random);
        test[i] = rrealloc(test[i], random);
        for (int j = 0; j < random; j++)
            test[i][j] = 0;
        i++;
    }
    // ffree(test[8]);
    // ffree(test[50]);
    // ffree(test[9]);
    show_alloc_mem();
}