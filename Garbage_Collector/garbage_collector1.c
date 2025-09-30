/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:39:30 by kskender          #+#    #+#             */
/*   Updated: 2025/09/30 17:45:17 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

// Cleanup all allocated memory and close all registered fds
void	gc_free(t_gc *gc, void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!gc || !ptr)
		return ;
	current = gc->head;
	prev = NULL;
	while (current)
	{
		if (current->type == GC_MEM && current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				gc->head = current->next;
			free(current->ptr);
			free(current);
			gc->count--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_close(t_gc *gc, int fd)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!gc || fd < 0)
		return ;
	current = gc->head;
	prev = NULL;
	while (current)
	{
		if (current->type == GC_FD && current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				gc->head = current->next;
			close(current->fd);
			free(current);
			gc->count--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// Cleanup everything
void	gc_cleanup(t_gc *gc)
{
	t_gc_node	*current;
	t_gc_node	*next;

	if (!gc)
		return ;
	current = gc->head;
	while (current)
	{
		next = current->next;
		if (current->type == GC_MEM)
			free(current->ptr);
		else if (current->type == GC_FD)
			close(current->fd);
		free(current);
		current = next;
	}
	free(gc);
}

// Utility functions
void	gc_print(t_gc *gc)
{
	t_gc_node	*current;
	int			i;

	if (!gc)
	{
		printf("GC is NULL\n");
		return ;
	}
	printf("GC has %zu items:\n", gc->count);
	current = gc->head;
	i = 0;
	while (current)
	{
		if (current->type == GC_MEM)
			printf(" [%d] MEM: %p\n", i, current->ptr);
		else if (current->type == GC_FD)
			printf(" [%d] FD: %d\n", i, current->fd);
		current = current->next;
		i++;
	}
}

size_t	gc_count(t_gc *gc)
{
	if (!gc)
		return (0);
	return (gc->count);
}
