
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:20:10 by kskender          #+#    #+#             */
/*   Updated: 2025/10/15 00:58:50 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

// Includes -- BEGIN
#include "garbage_collector.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>	// printf, fprintf, FILE, stderr
#include <stdlib.h> // malloc, free, getenv, setenv, NULL
#include <string.h> // strcmp, strcpy, strlen, strtok
#include <unistd.h> // chdir, getcwd, STDOUT_FILENO
#include <errno.h>	// errno, perror
#include <limits.h> // PATH_MAX
#include <sys/wait.h>
#include <string.h> // strchr

// Exported variables tracking (single global for 42 norm)
#define MAX_EXPORTED 128
typedef struct s_shell_state
{
	char *exported_vars[MAX_EXPORTED];
	int exported_count;
} t_shell_state;
t_shell_state g_shell;
typedef struct s_filelist
{
	// Enum completely removed
	char *filename;
	t_REDIR_TYPE type;
	struct s_filelist *next;
} t_filelist;

typedef struct s_commandlist
{
	t_filelist *files;
} t_commandlist;
// Includes -- END

// Basics --Begin
int outfile_redirector(t_file_node *file_node);
int infile_redirector(t_file_node *file_node);
void dup_and_or_close(int *prev_in_out, int *new_in_out);
void close_and_reset(int *prev_in_out, int *new_in_out,
					 int *reset);
int pipe_handler(t_cmd_node *command);
// Basics --End
// Redirectories-- BEGIN
int setup_output_file(t_commandlist *cmd);
int count_input(t_commandlist *cmd);
int count_output(t_commandlist *cmd);
int setup_input_file(t_commandlist *cmd);
int check_redirection(t_commandlist *cmd, int control,
					  int *reset);
// Redirectories -- END
// Export utility functions -- BEGIN
int is_valid_identifier(const char *name);
// Export utility functions -- END
#endif
