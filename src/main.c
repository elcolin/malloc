#include "../inc/malloc.h"

#include "time.h"
#include <stdlib.h>

void copy_print(char *dest, char *src)
{
    if (!src || !dest)
        return;
    strcpy(dest, src);
    //printf("src: %s\tlen: %ld\n", src, strlen(src));
    //printf("dest: %s\tlen: %ld\n", dest, strlen(dest));

}


int main()
{
    mmalloc(10);
    mmalloc(52);
    // {
    //     struct rlimit rlim;
    //     printf("%d\n", getrlimit(RLIMIT_AS, &rlim));
    //     printf("%ld\n", rlim.rlim_max);
    // }
    void *ptr = 0;

    ptr = mmalloc(48815);
    // ffree(ptr);
    ptr = mmalloc(485);

    ptr = rrealloc(ptr, 3600000000000093);
    ptr = mmalloc(4805);

    show_alloc_mem();
    printf("%d\n", getpagesize());
    // printf("%ld\n", HEAP_SIZE);
    // struct rlimit rlim;
    // printf("%d\n", getrlimit(RLIMIT_DATA, &rlim));
    // printf("%ld\n", rlim.rlim_max);
}