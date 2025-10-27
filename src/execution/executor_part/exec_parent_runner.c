/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent_runner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:14:57 by kskender          #+#    #+#             */
/*   Updated: 2025/10/23 22:05:19 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

static int setting_infile_and_outfile(t_cmd_node *cmd, int *io_data)
{
	int error_code;

	error_code = 0;
	if (io_data[0] != NO_REDIRECTION)
	{
		error_code = setup_input_file((t_commandlist *)cmd);
		io_data[2] = NO_REDIRECTION;
		io_data[4] = NO_REDIRECTION;
		if (error_code != EXIT_SUCCESS)
			return (error_code);
	}
	if (io_data[1] != NO_REDIRECTION)
	{
		error_code = setup_output_file((t_commandlist *)cmd);
		io_data[2] = NO_REDIRECTION;
		io_data[4] = NO_REDIRECTION;
		if (error_code != EXIT_SUCCESS)
			return (error_code);
	}
	return (error_code);
}

static int is_builtin_cmd(char **argv)
{
	if (!argv || !argv[0])
		return 0;
	if (!strcmp(argv[0], "echo"))
		return 1;
	if (!strcmp(argv[0], "cd"))
		return 1;
	if (!strcmp(argv[0], "pwd"))
		return 1;
	if (!strcmp(argv[0], "export"))
		return 1;
	if (!strcmp(argv[0], "unset"))
		return 1;
	if (!strcmp(argv[0], "env"))
		return 1;
	return 0;
}

pid_t exec_parent_runner(t_cmd_node *cmd, int *io_data)
{
	int error_code;
	char **envp;
	pid_t pid;

	error_code = setting_infile_and_outfile(cmd, io_data);
	dup_and_or_close(&io_data[2], &io_data[4]);
	if (error_code != EXIT_SUCCESS)
		return (-1);

	/* If this is a builtin, run it in the parent and return 0 (no child pid) */
	if (is_builtin_cmd(cmd->cmd))
	{
		envp = generate_env(cmd->env);
		table_of_builtins(cmd, envp, 1);
		return 0;
	}

	pid = fork();
	if (pid == 0)
	{
		if (io_data[0] != NO_REDIRECTION)
		{
			dup2(io_data[0], STDIN_FILENO);
			close(io_data[0]);
		}
		if (io_data[1] != NO_REDIRECTION)
		{
			dup2(io_data[1], STDOUT_FILENO);
			close(io_data[1]);
		}
		envp = generate_env(cmd->env);
		exec_external(cmd->cmd, envp);
		_exit(127);
	}
	if (pid > 0)
		return pid;
	perror("fork");
	return -1;
}
