/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:20:10 by kskender          #+#    #+#             */
/*   Updated: 2025/10/06 18:29:20 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// Includes -- BEGIN
# include "garbage_collector.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_redir_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	NO_REDIRECTION = -1
}						t_redir_type;

typedef struct s_filelist
{
	char				*filename;
	t_redir_type		type;
	struct s_filelist	*next;
}						t_filelist;

typedef struct s_commandlist
{
	t_filelist			*files;
}						t_commandlist;
// Includes -- END

// Basics --Begin
int						outfile_redirector(t_file_node *file_node);
int						infile_redirector(t_file_node *file_node);
void					dup_and_or_close(int *prev_in_out, int *new_in_out);
void					close_and_reset(int *prev_in_out, int *new_in_out,
							int *reset);
int						pipe_handler(t_cmd_node *command);
// Basics --End
// Redirectories-- BEGIN
int						setup_output_file(t_commandlist *cmd, t_gc *gc);
int						count_input(t_commandlist *cmd);
int						count_output(t_commandlist *cmd);
int						setup_input_file(t_commandlist *cmd);
int						check_redirection(t_commandlist *cmd, int control,
							int *reset);
// Redirectories -- END

#endif
