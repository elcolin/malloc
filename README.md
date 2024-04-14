# env variable
export LD_LIBRARY_PATH=$(pwd)

# How to use valgrind with my malloc implementation?

valgrind  --soname-synonyms=somalloc=libft_malloc.so ./a.out

gcc test/test0.c -L. -lft_malloc -> takes one integer
gcc test/test1.c -L. -lft_malloc -> takes two strings


## TODO
- Adapt size allocation
- Memory alignment pb (+ 8?)