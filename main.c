/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:58:58 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/17 16:16:46 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

static int handle_builtin(char **args)
{
    if (strcmp(args[0], "pwd") == 0)
        return (ft_pwd(args));
    if (strcmp(args[0], "echo") == 0)
        return (ft_echo(args));
    if (strcmp(args[0], "cd") == 0)
        return (ft_cd(args));
    if (strcmp(args[0], "export") == 0)
        return (ft_export(args));
    if (strcmp(args[0], "unset") == 0)
        return (ft_unset(args));
    if (strcmp(args[0], "env") == 0)
        return (ft_env(args));
    return (0);
}

static int run_external(char **args, int in_fd, int out_fd)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (in_fd != -1)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != -1)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        extern char **environ;

        exec_external(args, environ);
        fprintf(stderr, "%s: command not found\n", args[0]);
        _exit(127);
    }
    if (in_fd != -1)
        close(in_fd);
    if (out_fd != -1)
        close(out_fd);
    if (pid > 0)
    {
        int status;

        waitpid(pid, &status, 0);
    }
    else
        perror("fork");
    return (0);
}

static int handle_redirections(char **args, int *in_fd, int *out_fd)
{
    if (setup_redirections(args, in_fd, out_fd))
    {
        perror("redirection");
        return (1);
    }
    return (0);
}

int main(void)
{
    char input[1024];
    char *args[32];

    while (1)
    {
        printf("minishell$ ");
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "exit") == 0)
            break;
        split_args(input, args, 32);
        if (args[0] == NULL)
            continue;
        if (handle_builtin(args))
            continue;
        int in_fd;
        int out_fd;

        if (handle_redirections(args, &in_fd, &out_fd))
            continue;
        run_external(args, in_fd, out_fd);
    }
    return (0);
}
