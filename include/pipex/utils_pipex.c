/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kskender <kskender@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:16:10 by kskender          #+#    #+#             */
/*   Updated: 2025/09/26 14:44:52 by kskender         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "pipex.h"

void	handle_exit(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(n_exit);
}

int	open_file(char *file, int inf_or_ouf)
{
	int	res;

	if (inf_or_ouf == 0)
		res = open_infile(file);
	else
		res = open_outfile(file, false);
	if (res == -1)
	{
		ft_putstr_fd("pipex: failed to open file\n: ", 2);
		ft_putendl_fd(file, 2);
		exit(1);
	}
	return (res);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*temp;

	allpath = ft_split(get_env("PATH", env), ';');
	i = -1;
	while (allpath && allpath[++i])
	{
		temp = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(temp, cmd);
		free(temp);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	return (cmd);
}
