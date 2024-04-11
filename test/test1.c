#include "../inc/malloc.h"

#include <stddef.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        ft_putstr_fd("Wrong number of arguments\n", 2);
        return 1;
    }

    char *test;

    size_t len1 = ft_strlen(argv[1]) + 1, len2 = ft_strlen(argv[2]) + 1;

    test = malloc(len1);
    ft_strlcpy(test, argv[1], len1);
    show_alloc_mem();
    ft_putstr_fd("\t-- after malloc --\n",1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\n ",1);
    test = realloc(test, len2);

    ft_putstr_fd("\t-- after realloc before copy --\n",1);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\n ",1);

    ft_putstr_fd("\t -- after realloc and copy --\n",1);
    ft_strlcpy(test, argv[2], len2);
    ft_putstr_fd(test, 1);
    ft_putstr_fd("\n ",1);
    show_alloc_mem();

    free(test);
    ft_putstr_fd("\t-- after free --\n",1);
    show_alloc_mem();
    
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize < 1)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}



size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}