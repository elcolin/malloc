#include <stdlib.h>
#include <string.h>
#include <unistd.h>
# include "inc/malloc.h"


void    print(char *s)
{
    write(1, s, strlen(s));
}

int     main(void)
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024) 
    {
        addr = (char*)malloc(1024);
        if (addr == NULL)
        {
            print("Failed to allocate memory\n");
            return (1);
        }
        addr[0] = 42;
        free(addr); 
        i++; 
    }
    show_alloc_mem();
    return (0);
}
