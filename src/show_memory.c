#include "../inc/malloc.h"

extern t_heap *heap_lst;

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	m;

	m = n;
	if (m < 0)
		m *= -1;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (m >= 10)
		ft_putnbr_fd(m / 10, fd);
	ft_putchar_fd(m % 10 + '0', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void addr_to_str(void *addr)
{
    char    *hexbase = "0123456789ABCDEF";
    char    str[12] = {0};
    unsigned long int   res = (long unsigned int) addr;
    int i = 12;

    while (i--)
    {
        // //printf("%d\n", i);
        str[i] = hexbase[0xF & res];
        res = res >> 4;
    }
    ft_putstr_fd("0x", 1);
    ft_putstr_fd(str, 1);
    // //printf("0x%s\n", str);
}

void print_block(t_block *first)
{
    while (first)
    {
        // //printf("\t%p - %p: %ld\tisfree: %d\n", (void *) first, (void *) first + first->data_size, first->data_size, first->freed);
        // //printf("isfreed: %d", first->freed);
        addr_to_str((void *) first);
        ft_putstr_fd(" - ", 1);
        addr_to_str((void *) (void *) first + BLOCK_SIZE + first->data_size);
        ft_putstr_fd(" : ", 1);
        ft_putnbr_fd(first->data_size + BLOCK_SIZE, 1);
        ft_putstr_fd(" bytes\n", 1);
        first = first->next;
    }
    
}

void show_alloc_mem()
{
    char *label_str[3] = {"TINY", "SMALL", "LARGE"};

    t_heap *index = heap_lst;
    size_t total_allocated = 0;
    // while (index)
    // {
    //     //printf("%s  :  %p\n", label_str[index->label_size], (void *)index);
    //     print_block(HEAP_SHIFT(index));
    //     // itox(HEAP_SHIFT(index));
    //     index = index->next;
    // }
    while (index)
    {
        //printf("%s  :  %p\n", label_str[index->label_size], (void *)index);
        ft_putstr_fd(label_str[index->label_size], 1);
        ft_putstr_fd(" : ", 1);
        addr_to_str((void *) index);
        ft_putstr_fd("\tsize: ", 1);
        ft_putnbr_fd(index->total_size, 1);
        ft_putstr_fd("\n", 1);
        print_block(HEAP_SHIFT(index));
        total_allocated += index->total_size;
        // itox(HEAP_SHIFT(index));
        index = index->next;
    }
    ft_putstr_fd("Total : ", 1);
    ft_putnbr_fd(total_allocated, 1);
    ft_putstr_fd(" bytes\n", 1);
}