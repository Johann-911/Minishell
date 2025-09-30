/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:00:04 by kskender          #+#    #+#             */
/*   Updated: 2025/09/26 17:42:55 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_heredoc_tempfiles(t_cmd_node *command, t_env_list *env,
		int heredoc_count)
{
	t_file_node	*current_file;
	char		*temp_filename;

	if (!command || !command->files)
		return (heredoc_count);
	current_file = command->files->head;
	while (current_file != NULL)
	{
		if (current_file->redir_type == TK_HEREDOC)
		{
			temp_filename = setup_heredoc_document(file_node, env_list,
					count_heredocs);
			if (temp_filename == NULL)
				return (-1);
			count_heredocs++;
		}
		file_node = file_node->next;
	}
	return (count_heredocs);
}

int	redir_infiles_loops(t_cmd_node *cmd_node)
{
	t_file_node	*file_node;
	int			infile_stat;
	int			return_value;

	return_value = 0;
	infile_stat = INFILE_NOT_USED;
	if (cmd_node == NULL || cmd_node->files == NULL)
		return (INFILE_NOT_USED);
	file_node = cmd_node->files->head;
	while (file_node != NULL)
	{
		if (file_node->redir_type == HEREDOC)
			return_value = redir_heredoc(file_node);
		else if (file_node->redir_type == INFILE)
			return_value = redir_infile(file_node);
		if (return_value == -1)
			return (-1);
		if (return_value == INFILE_USED)
			infile_stat = INFILE_USED;
		file_node = file_node->next;
	}
	return (infile_stat);
}

int	redir_outfiles_loops(t_cmd_node *cmd_node)
{
	t_file_node	*file_node;
	int			outfile_stat;
	int			return_value;

	return_value = 0;
	outfile_stat = OUTFILE_NOT_USED;
	if (cmd_node == NULL || cmd_node->files == NULL)
		return (OUTFILE_NOT_USED);
	file_node = cmd_node->files->head;
	while (file_node != NULL)
	{
		if (file_node->redir_type == HEREDOC)
			return_value = redir_outfile(file_node);
		else if (file_node->redir_type == TK_APPEND)
			return_value = redir_append(file_node);
		if (return_value == -1)
			return (-1);
		if (return_value == OUTFILE_USED)
			outfile_stat = OUTFILE_USED;
		file_node = file_node->next;
	}
	return (outfile_stat);
}
