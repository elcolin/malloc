#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include "inc/malloc.h"

void print(char *s)
{
    write(1, s, strlen(s));
}

int     main()
{
    int     i;
    int     alignment;
    char    *addr;

    i = 1;
    alignment = 2 * sizeof(size_t);
    // printf("%d\n",alignment);
    while (i <= 100)
    {
        addr = (char*)malloc(i);
		// show_alloc_mem();
        if (addr == NULL)
        {
            print("Failed to allocate memory\n");
            exit(1);
        }
        if ((((unsigned long) (addr)) % alignment) != 0)
        {
            printf("pb: %lu\n",(unsigned long) (addr) % alignment);
            print("malloc returned a non aligned boundary\n");
            exit(1);
        }
        i++;
        free(addr);
    }
}
