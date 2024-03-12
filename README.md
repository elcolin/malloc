# malloc
 This project is about implementing a dynamic memory allocation mechanism.


REMPLACER TOUS LES STRLEN

get system limit!


Last error to date:

            -- reallocating i: 40 for size 8--
    heap: 0x7fd56d2e8000     block: 0x7fd56d2e804c
            Size below allocation
    AddressSanitizer:DEADLYSIGNAL
    =================================================================
    ==707975==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x5573dfb81845 bp 0x7ffc08ebd480 sp 0x7ffc08ebd460 T0)
    ==707975==The signal is caused by a READ memory access.
    ==707975==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
        #0 0x5573dfb81845 in cut_block src/block.c:48
        #1 0x5573dfb832a3 in rrealloc src/realloc.c:22
        #2 0x5573dfb82cb8 in main src/main.c:65
        #3 0x7fd570095d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
        #4 0x7fd570095e3f in __libc_start_main_impl ../csu/libc-start.c:392
        #5 0x5573dfb813a4 in _start (/mnt/nfs/homes/ecolin/42/post-cc/malloc/a.out+0x23a4)

    AddressSanitizer can not provide additional info.
    SUMMARY: AddressSanitizer: SEGV src/block.c:48 in cut_block

make cutblock use mergeblock if necessary (for if next is free)