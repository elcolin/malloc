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

    ptr = mmalloc(3693);
    ffree(ptr);
    ptr = rrealloc(ptr, 48815);
    show_alloc_mem();
    // struct rlimit rlim;
    // printf("%d\n", getrlimit(RLIMIT_DATA, &rlim));
    // printf("%ld\n", rlim.rlim_max);
}