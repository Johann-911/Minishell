#ifndef GC_H
# define GC_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

/*
** ───────────────────────────────────────────────
** Garbage Collector Node
** ───────────────────────────────────────────────
*/
typedef struct s_gc
{
    void    	*ptr;
	struct s_gc	*next;
} t_gc;

/*
** ───────────────────────────────────────────────
** GC API
** ───────────────────────────────────────────────
*/

//Allocate memory tracked by GC
void *gc_malloc(size_t size);

//Manually add already allocated pointer
void gc_add(void *ptr);

//Free all tracked memory
void gc_free_all(void);

//Free a command linked list
int gc_remove(void *ptr);

//Free a redirection linked list
size_t  gc_count(void);

#endif