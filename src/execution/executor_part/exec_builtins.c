/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:32:23 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/23 22:05:21 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

char **generate_env(t_env_list *env)
{
    char **envp;
    t_env_node *cur;
    int i = 0;

    if (!env)
        return (NULL);
    envp = gc_malloc(sizeof(char *) * (env->size + 1));
    if (!envp)
        return (NULL);
    cur = env->head;
    while (cur)
    {
        char *tmp = ft_strjoin(cur->type, "=");
        envp[i++] = ft_strjoin(tmp, cur->value);
        gc_free(tmp);
        cur = cur->next;
    }
    envp[i] = NULL;
    return (envp);
}

int table_of_builtins(t_cmd_node *cmd, char **envp, int flag)
{
    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return (-1);
    if (!strcmp(cmd->cmd[0], "echo"))
        return (ft_echo(cmd->cmd));
    if (!strcmp(cmd->cmd[0], "pwd"))
        return (ft_pwd(cmd->cmd));
    if (!strcmp(cmd->cmd[0], "cd"))
        return (ft_cd(cmd->cmd));
    if (!strcmp(cmd->cmd[0], "export"))
        return (ft_export(cmd->cmd));
    if (!strcmp(cmd->cmd[0], "unset"))
        return (ft_unset(cmd->cmd));
    if (!strcmp(cmd->cmd[0], "env"))
        return (ft_env(cmd->cmd));
    /* not a builtin */
    (void)envp;
    (void)flag;
    return (128);
}

/*
** Checks if the argument is a valid -n option for echo
*/
static int is_n_option(char *arg)
{
    int i;

    if (!arg || arg[0] != '-')
        return (0);
    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (i > 1);
}

/*
** Prints the value of an environment variable if the argument starts with '$'
*/
static void echo_expand_and_print(char *arg)
{
    if (arg[0] == '$' && arg[1])
    {
        char *val = getenv(arg + 1);
        if (val)
            ft_putstr_fd(val, STDOUT_FILENO);
    }
    else
        ft_putstr_fd(arg, STDOUT_FILENO);
}

/*
** 42 norm-adaptable echo builtin with $VAR expansion
*/
static void echo_print_range(char **args, int start_index)
{
    int i;

    i = start_index;
    while (args[i])
    {
        echo_expand_and_print(args[i]);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
}

int ft_echo(char **args)
{
    int nl_option;
    int start_index;

    nl_option = 0;
    start_index = 1;
    if (args[1])
    {
        while (args[start_index] && is_n_option(args[start_index]))
        {
            nl_option = 1;
            start_index++;
        }
    }
    echo_print_range(args, start_index);
    if (!nl_option)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}

int ft_pwd(char **args)
{
    char cwd[4096];
    (void)args;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 0;
    }
    perror("pwd");
    return 1;
}