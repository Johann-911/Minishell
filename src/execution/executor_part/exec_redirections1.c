/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:43:35 by kskender          #+#    #+#             */
/*   Updated: 2025/10/06 18:28:48 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// OUTPUT STARTS HERE FOR REDIRECTIONS
static t_filelist	*find_last_output(t_commandlist *cmd, int output_count)
{
	int			current_count;
	t_filelist	*current;

	current_count = 0;
	current = cmd->files;
	while (current != NULL)
	{
		if (current->type == OUTFILE || current->type == APPEND)
		{
			current_count++;
			if (current_count == output_count)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

int	setup_output_file(t_commandlist *cmd, t_gc *gc)
{
	int			output_count;
	t_filelist	*last_output;
	int			fd;
	int			flags;

	output_count = count_output(cmd);
	if (output_count == 0)
		return (NO_REDIRECTION);
	last_output = find_last_output(cmd, output_count);
	if (last_output == NULL)
		return (NO_REDIRECTION);
	flags = O_WRONLY | O_CREAT;
	if (last_output->type == OUTFILE)
		flags |= O_TRUNC;
	else if (last_output->type == APPEND)
		flags |= O_APPEND;
	fd = gc_open(gc, last_output->filename, flags, 0644);
	return (fd);
}
