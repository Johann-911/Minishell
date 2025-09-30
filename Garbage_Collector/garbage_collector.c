/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:08:39 by kskender          #+#    #+#             */
/*   Updated: 2025/09/30 16:38:37 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

// initializing gc
t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->head = NULL;
	gc->count = 0;
	return (gc);
}

int	gc_add_node(t_gc *gc, void *ptr, int fd, t_gc_type type)
{
	t_gc_node	*new_node;

	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return (0);
	new_node->ptr = ptr;
	new_node->fd = fd;
	new_node->type = type;
	new_node->next = gc->head;
	gc->head = new_node;
	gc->count++;
	return (1);
}

// memory allocations Basics
void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_add_node(gc, ptr, -1, GC_MEM))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

void	*gc_calloc(t_gc *gc, size_t count, size_t size)
{
	void	*ptr;

	ptr = calloc(count, size);
	if (!ptr)
		return (NULL);
	if (!gc_add_node(gc, ptr, -1, GC_MEM))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

// Registring file descriptors
void	gc_register_fd(t_gc *gc, int fd)
{
	if (fd < 0)
		return ;
	gc_add_node(gc, NULL, fd, GC_FD);
}
