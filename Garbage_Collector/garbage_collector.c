#include "../include/garbage_collector.h"

static t_gc *g_head = NULL;

//allocate memory and track it
void    *gc_malloc(size_t size)
{
    void    *mem;
    t_gc    *node;

    mem = malloc(size);
    if(!mem)
        return(NULL);
    node = malloc(sizeof(t_gc));
    if(!node)
    {
        free(mem);
        return(NULL);
    }
    node->ptr = mem;
    node->next = g_head;
    g_head = node;
    return(mem);
}

//Track an exisiting pointer
void    gc_add(void *ptr)
{
    t_gc    *node;
    if(!ptr)
        return(0);
    node = malloc(sizeof(t_gc));
    if(!node)
        return(-1);
    node->ptr = ptr;
    node->next = g_head;
    g_head = node;
    return(0);
}

//Free all tracked pointers
void    gc_free_all(void)
{
    t_gc    *temp;

    while(g_head)
    {
        temp = g_head;
        g_head = g_head->next;
        free(temp ->ptr);
        free(temp);
    }
}

//Free a redirection linked list

void gc_free_redirs(t_redir *redirs)
{
    t_redir *temp;

    while(redirs)
    {
        temp = redirs;
        redirs = redirs->next;
        if(temp->target)
            free(temp->target);
        free(temp);
    }
}

//Free a command linked list and its redirections

void    gc_free_cmd_list(t_cmd *cmds)
{
    t_cmd   *temp;
    int     i;

    while(cmds)
    {
        temp = cmds;
        cmds = cmds->next;
        if(temp->av)
        {
            i = 0;
            while (temp->av[i])
                free(temp->av[i++]);
            free(temp->av);
        }
        if(temp->redirs)
            gc_free_redirs(temp->redirs);
        free(temp);
    }
}