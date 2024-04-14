#include "time.h"
#include <limits.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr);


int main(int argc, char *argv[])
{
    char *test[100] = {0};
    if (argc != 2)
    {
        // ft_putstr_fd("Wrong number of arguments\n", 2);
        return 1;
    }

    size_t random = 0;
    size_t max_mem = ft_atoi(argv[1]);
    if (max_mem > INT_MAX || max_mem < 0)
    {
        // ft_putstr_fd("Incorrect argument: Is argument negative or above int max?\n", 2);
        return 1;
    }
    srand(time(NULL));
    size_t j = 0;

    for (int i = 0; i < 100; i++)
    {
        random = rand() % 100;
        if (!test[random])
        {
            j = rand() % (max_mem + 1);
            if (!max_mem)
                j = 0;
            test[random] = malloc(j);
            while (j--)
                test[random][j] = 'a';
        }
    }
    // show_alloc_mem();
    // ft_putstr_fd("\t--- AFTER MALLOC ---\n", 1);
    for (int i = 0; i < 100; i++)
    {
        random = rand() % 100;
        j = rand() % (max_mem + 1);
        if (!max_mem)
            j = 0;
        test[random] = realloc(test[random], j);
        // printf("%d\n", j);
        if (j)
            test[random][--j] = '\0';
        while (j--)
            test[random][j] = 'a';
    }
    // show_alloc_mem();
    // ft_putstr_fd("\t--- AFTER REALLOC ---\n", 1);

    for (int i = 0; i < 100; i++)
        free(test[i]);
    // show_alloc_mem();
    // ft_putstr_fd("\t--- AFTER FREE ---\n", 1);

}


int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		p;

	i = 0;
	res = 0;
	p = 1;
	while ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		p = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (res * p);
		res += nptr[i] - '0';
		i++;
		if (nptr[i] != '\0' && (nptr[i] <= '9' && nptr[i] >= '0'))
			res *= 10;
	}
	return (res * p);
}
