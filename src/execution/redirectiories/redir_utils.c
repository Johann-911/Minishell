/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:43:35 by kskender          #+#    #+#             */
/*   Updated: 2025/09/26 23:01:32 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	file_redirector(t_cmd_node *cmd_node)
{
	if (redir_infiles_loops(cmd_node) == -1)
		return (-1);
	if (redir_outfiles_loops(cmd_node) == -1)
		return (-1);
	return (0);
}

void	delete_all_temp_files(const char *folder_name)
{
	DIR				*dir;
	struct dirent	*file;
	char			*temp_str;
	char			*file_name;

	dir = opendir(folder_name);
	if (!dir)
		return ;
	file = readdir(dir);
	while (file != NULL)
	{
		if (strncmp(file->d_name, ".here_doc", 9) == 0)
		{
			temp_str = ft_strjoin(folder_name, "/");
			file_name = ft_strjoin(temp_str, file->d_name);
			free(temp_str);
			unlink(file_name);
			free(file_name);
		}
		file = readdir(dir);
	}
	closedir(dir);
}

void	set_interactive_mode(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd == -1)
	{
		ft_putstr_fd("Error: Unable to open /dev/tty\n", 2);
		return ;
	}
	dup2(tty_fd, STDIN_FILENO);
	dup2(tty_fd, STDOUT_FILENO);
	close(tty_fd);
}

void	doc_expander_writer(char *line, int write_fd, t_env_list *env_list)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	token->value = gc_strdup(line);
	token->segment_list = NULL;
}
