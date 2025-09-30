/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:20:10 by kskender          #+#    #+#             */
/*   Updated: 2025/09/26 22:49:54 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// Includes -- BEGIN
# include "minishell.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum FILE_CHECK // got the redirecting types for the files
{
	OUTFILE_NOT_USED,
	OUTFILE_USED,
	INFILE_NOT_USED,
	INFILE_USED
}							t_file_check;

// Includes -- END

typedef struct s_cmd_list	t_cmd_list;

// Redirections --BEGIN
int							redir_infile(t_file_node *file_node);
int							redir_heredoc(t_file_node *file_node);
int							redir_outfile(t_file_node *file_node);
int							redir_append(t_file_node *file_node);
// Redirections --END

// Redirectory loops -- BEGIN
int							handle_heredoc_tempfiles(t_cmd_node *command,
								t_env_list *env, int heredoc_count);
int							redir_infiles_loops(t_cmd_node *cmd_node);
int							redir_outfiles_loops(t_cmd_node *cmd_node);
// Redirectory loops -- END

// Redirectory utils -- BEGIN
int							file_redirector(t_cmd_node *cmd_node);
void						delete_all_temp_files(const char *folder_name);
void						set_interactive_mode(void);
void 					  doc_expander_writer(char *line, int write_fd, t_env_list *env_list);
//Redirectory utils -- BEGIN

#endif
