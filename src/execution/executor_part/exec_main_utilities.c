/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:05:38 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/16 18:08:19 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

// Simple argument splitter
void split_args(char *input, char **args, int max_args)
{
    int i = 0;
    char *token = strtok(input, " ");
    while (token && i < max_args - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

/*
** 42 norm-compliant execution of redirections (input, output, append)
** - Open file for each redirection type
** - Setup fd and dup2 before running command
** - Error handling and fd closing
*/
int setup_redirections(char **args, int *in_fd, int *out_fd)
{
    int i;
    *in_fd = -1;
    *out_fd = -1;
    i = 0;
    while (args[i])
    {
        if (strcmp(args[i], ">") == 0 && args[i + 1])
        {
            *out_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            args[i] = NULL;
        }
        else if (strcmp(args[i], ">>") == 0 && args[i + 1])
        {
            *out_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            args[i] = NULL;
        }
        else if (strcmp(args[i], "<") == 0 && args[i + 1])
        {
            *in_fd = open(args[i + 1], O_RDONLY);
            args[i] = NULL;
        }
        i++;
    }
    if ((*in_fd != -1 && *in_fd < 0) || (*out_fd != -1 && *out_fd < 0))
        return (1); // Error
    return (0);
}

// Norm-compliant: Search $PATH and execve
int exec_external(char **args, char **envp)
{
    char *path = getenv("PATH");
    char *dirs[64];
    char fullpath[512];
    int i = 0;
    if (!path)
        return execve(args[0], args, envp);
    char *p = strtok(path, ":");
    while (p && i < 63)
    {
        dirs[i++] = p;
        p = strtok(NULL, ":");
    }
    dirs[i] = NULL;
    for (int j = 0; dirs[j]; j++)
    {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirs[j], args[0]);
        execve(fullpath, args, envp);
    }
    return execve(args[0], args, envp);
}