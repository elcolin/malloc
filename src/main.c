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


// int main(){

//     char *test[100] = {"100"};
//     int i = 100;
//     int random;
//     srand(time(NULL));
//     while (i)
//     {
//         i--;
//         random = rand() % 10 + 1;
//         test[i] = mmalloc(random);
//         //printf("\t-- Allocating i: %d %p--\n", i, test[i]);
//         for (int j = 0; j < random; j++)
//             test[i][j] = 1;
//     }
//     i = 100;
//     show_alloc_mem();

//     while (i)
//     {
//         i--;
//         //printf("\t-- Freeing i: %d %p --\n", i, test[i]);
//         // if (i != 2 && i !=8 && i!= 49 && i!= 9)
//             ffree(test[i]);
//     }
//     show_alloc_mem();
//     i = 100;
//      while (i)
//     {
//         i--;
//         random = rand() % 100;
//         //printf("\t-- reallocating i: %d %p for size %d --\n", i, BLOCK_SHIFT(test[i]), random);
//         test[i] = rrealloc(test[i], random);
//         // show_alloc_mem();
//         for (int j = 0; j < random; j++)
//             test[i][j] = 0;
//     }
//     i=25;
//     while (i)
//     {
//         i--;
//         //printf("\t-- Freeing i: %d %p --\n", i, test[i]);
//         // if (i != 2 && i !=8 && i!= 49 && i!= 9)
//             ffree(test[i]);
//     }
//     i = 75;
//      while (i)
//     {
//         i--;
//         random = rand() % 1000;
//         //printf("\t-- reallocating i: %d %p for size %d--\n", i, BLOCK_SHIFT(test[i]), random);
//         test[i] = rrealloc(test[i], random);
//         // show_alloc_mem();
//         for (int j = 0; j < random; j++)
//             test[i][j] = 0;
//     }
//     i=100;
//     show_alloc_mem();
//     while (i)
//     {
//         i--;
//         //printf("Freeing i: %d %p\n", i, test[i]);
//         // if (i != 2 && i !=8 && i!= 49 && i!= 9)
//             ffree(test[i]);
//     }
//     show_alloc_mem();

// }

    // i = 2100;
    // while (i < 1000)
    // {
    //     //printf("Freeing i: %d %p\n", i, test[i]);
    //     if (i != 2 && i !=8 && i!= 49 && i!= 9)
    //         ffree(test[i]);
    //     i++;
    // }
    // i = 99;
    //  while (i)
    // {
    //     random = rand() % 100;
    //     //printf("\t-- reallocating i: %d for size %d--\n", i, random);
    //     test[i] = rrealloc(test[i], random);
    //     for (int j = 0; j < random; j++)
    //         test[i][j] = 0;
    //     i--;
    // }
    // i = 100;
    //  while (i)
    // {
    //     i--;
    //     //printf("Freeing i: %d\n", i);
    //         ffree(test[i]);
    // }
    // show_alloc_mem();

void copy_print(char *dest, char *src)
{
    if (!src || !dest)
        return;
    strcpy(dest, src);
    //printf("src: %s\tlen: %ld\n", src, strlen(src));
    //printf("dest: %s\tlen: %ld\n", dest, strlen(dest));

}

// void addr_to_str(void *addr)
// {
//     char    *hexbase = "0123456789ABCDEF";
//     char    str[12] = {0};
//     unsigned long int   res = (long unsigned int) addr;
//     int i = 12;

//     while (i--)
//     {
//         //printf("%d\n", i);
//         str[i] = hexbase[0xF & res];
//         res = res >> 4;
//     }
//     //printf("0x%s\n", str);
// }

// int main(int argc, char *argv[])
// {
//     if (argc != 3)
//     {
//         //write
//         //printf("Wrong number of arguments\n");
//         return 1;
//     }
//     //printf("str: %s\tlen: %ld\n", argv[1], strlen(argv[1]));
//     char *test = mmalloc(strlen(argv[1]));
//     copy_print(test, argv[1]);
//     show_alloc_mem();
//     test = rrealloc(test, strlen(argv[2]));
//     copy_print(test, argv[2]);
//     show_alloc_mem();
// }

int main()
{
    mmalloc(10);
    mmalloc(52);
    mmalloc(3693);
    mmalloc(48815);
    show_alloc_mem();
}