/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:00:04 by kskender          #+#    #+#             */
/*   Updated: 2025/10/15 00:51:55 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// Redirections count starts here
int count_input(t_commandlist *cmd)
{
	t_filelist *current;
	int count;

	count = 0;
	current = cmd->files;
	while (current != NULL)
	{
		if (current->type == INFILE || current->type == HEREDOC)
			count++;
		current = current->next;
	}
	return (count);
}

int count_output(t_commandlist *cmd)
{
	t_filelist *current;
	int count;

	count = 0;
	current = cmd->files;
	while (current != NULL)
	{
		if (current->type == OUTFILE || current->type == OUTFILE_APPEND)
			count++;
		current = current->next;
	}
	return (count);
}

// INPUT STARTS HERE FOR REDIRECTIONS
static t_filelist *find_last_input(t_commandlist *cmd, int input_count)
{
	int current_count;
	t_filelist *current;

	current_count = 0;
	current = cmd->files;
	while (current != NULL)
	{
		if (current->type == INFILE || current->type == HEREDOC)
		{
			current_count++;
			if (current_count == input_count)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

int setup_input_file(t_commandlist *cmd)
{
	int input_count;
	t_filelist *last_input;
	int fd;
	// t_gc *gc; // Removed unused variable
	input_count = count_input(cmd);
	if (input_count == 0)
		return (NO_REDIRECTION);
	last_input = find_last_input(cmd, input_count);
	if (last_input == NULL)
		return (NO_REDIRECTION);
	fd = gc_open(last_input->filename, O_RDONLY, 0);
	return (fd);
}
