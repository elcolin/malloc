#include "malloc.h"

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

    void *test;
    // size_t  test = (4 * getpagesize());
    // printf("TINYBLOCK: %u\t", TINY_BLOCK_SIZE);
    // printf("SMALLBLOCK: %u\n",SMALL_BLOCK_SIZE);
    test = mmalloc(5);
    for (int i = 0; i < 4; i++)
    {
        *((char *)(test + i)) = 'a';
    }
    *((char *)(test + 4)) = '\0';
    printf("\t%p %s\n", test, (char *)test);
    void *test2 = mmalloc(2);
    for (int i = 0; i < 15; i++)
    {
        *((char *)(test2 + i)) = 'b';
    }
    *((char *)(test2 + 15)) = '\0';
    printf("\t%s%s\n", (char *)test2, (char *)test);
    ffree(test);
    test = mmalloc(5);
    for (int i = 0; i < 4; i++)
    {
        *((char *)(test + i)) = '8';
    }
    printf("\t%p %s\n", test, (char *)test);
    printf("\t%s%s\n", (char *)test2, (char *)test);


    int i = 0;
    int random;
    srand(time(NULL));
    while (i < 100)
    {

        random = rand() % 100000 + 1;
        test = mmalloc(random);
        i++;
    }
}