/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:02:10 by kskender          #+#    #+#             */
/*   Updated: 2025/10/06 17:18:29 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
#include "parser.h"
# include <sys/stat.h>
# include <unistd.h>

typedef enum e_gc_type
{
	GC_MEM,
	GC_FD
}						t_gc_type;

typedef struct s_gc_node
{
	void				*ptr;
	int					fd;
	t_gc_type			type;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc
{
	t_gc_node			*head;
	size_t				count;
}						t_gc;

// Global GC access
t_gc_collector			*get_gc(void);
// Core GC initialization and cleanup
t_gc					*gc_init(void);
void					gc_cleanup(void);
int						gc_add_node(void *ptr, int fd, t_gc_type type);

// Basic memory management
void					*gc_malloc(size_t size);
void					*gc_calloc(size_t count, size_t size);

// Basic file descriptor management
void					gc_register_fd(int fd);

// Individual cleanup
void					gc_free(void *ptr);
void					gc_close(int fd);

// Utility functions
void					gc_print(void);
size_t					gc_count(void);

// String utilities
char					*gc_strdup(const char *s);
char					*gc_strndup(const char *s, size_t n);
char					**gc_split(const char *s, char c);

// File descriptor utilities
int						gc_open(const char *path, int flags, ...);
int						gc_pipe(int pipefd[2]);
int						gc_dup(int oldfd);
int						gc_dup2(int oldfd, int newfd);

#endif