#include "malloc.h"
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
    printf("TINYBLOCK: %u\t", TINY_BLOCK_SIZE);
    printf("SMALLBLOCK: %u\n",SMALL_BLOCK_SIZE);
    test = malloc(12);
    (void) test;
}