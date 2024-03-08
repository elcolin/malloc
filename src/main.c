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

    void *test[100];
    int i = 0;
    int random;
    srand(time(NULL));
    while (i < 100)
    {
        printf("Allocating i: %d\n", i);
        random = rand() % 100000 + 1;
        test[i] = mmalloc(random + 1);
        i++;
    }
    i = 0;
    while (i < 50)
    {
        printf("Freeing i: %d\n", i);
        ffree(test[i]);
        i++;
    }
    i = 0;
    while (i < 50)
    {
        printf("Allocating i: %d\n", i);
        random = rand() % 100000 + 1;
        test[i] = mmalloc(random + 1);
        i++;
    }
    i = 0;
    ffree(test[2]);
    ffree(test[8]);
    ffree(test[49]);
    ffree(test[9]);
    // while (i < 100)
    // {
    //     printf("Freeing i: %d\n", i);
    //     if (i != 2 && i !=8 && i!= 49 && i!= 9)
    //         ffree(test[i]);
    //     i++;
    // }
    // ffree(test[8]);
    // ffree(test[50]);
    // ffree(test[9]);
    show_alloc_mem();
}