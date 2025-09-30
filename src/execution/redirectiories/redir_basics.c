/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:53:50 by kskender          #+#    #+#             */
/*   Updated: 2025/09/30 16:30:13 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	redir_infile(t_file_node *file_node)
{
	int	fd;

	if (access(file_node->filename, F_OK) != 0)
	{
		ft_putstr_fd("Error: No such file or directory: ", 2);
		return (-1);
	}
	fd = open(file_node->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Unable to open infile\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error while dup2 (infile)\n", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (INFILE_USED);
}

int	redir_heredoc(t_file_node *file_node)
{
	int	fd;

	if (g_sigint_status == 2)
		return (-1);
	fd = open(file_node->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Unable to open heredoc file\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error while dup2 (heredoc)\n", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (INFILE_USED);
}

char	*generate_heredoc_tempfile(t_file_node *heredoc_node, t_env_list *env,
		int doc_number)
{
	int		output_fd;
	char	*file_path;
	char	*clean_filename;
	char	*full_temp_path;

	if (is_interactive_shell())
	{
		configure_terminal_for_heredoc();
		start_heredoc_signals();
	}
	clean_filename = sanitize_heredoc_delimiter(heredoc_node->filename,
			doc_number);
	full_temp_path = gc_strjoin("/tmp/.minishell_heredoc_", clean_filename);
	output_fd = open(full_temp_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		return (print_error("Heredoc: Cannot create temp file"), NULL);
	if (process_heredoc_input(heredoc_node, env, output_fd) != 0)
	{
		close(output_fd);
		return (NULL);
	}
	heredoc_node->filename = full_temp_path;
	close(output_fd);
	if (is_interactive_shell())
		restore_normal_signals();
	return (full_temp_path);
}

int	redir_outfile(t_file_node *file_node)
{
	int	fd;

	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Unable to open outfile\n", 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error while dup2 (outfile)\n", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (OUTFILE_USED);
}

int	redir_append(t_file_node *file_node)
{
	int	fd;

	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Unable to open outfile (append)\n", 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error while dup2 (append)\n", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (OUTFILE_USED);
}
