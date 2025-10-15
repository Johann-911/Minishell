/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:32:23 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/15 14:33:03 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

char **generate_env(t_env_list *env)
{
    (void)env;
    return (NULL);
}

int table_of_builtins(t_cmd_node *cmd, char **envp, int flag)
{
    (void)cmd;
    (void)envp;
    (void)flag;
    return 0;
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
int ft_echo(char **args)
{
    int nl_option;
    int i;
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
    i = start_index;
    while (args[i])
    {
        echo_expand_and_print(args[i]);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
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