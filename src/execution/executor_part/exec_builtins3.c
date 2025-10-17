/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:06:11 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/15 19:44:04 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// Add or update environment variables, bash-like

// Print all exported variables (env + exported-but-unset)
void print_exported_env(void)
{
    extern char **environ;
    int i = 0;
    char *eq;
    while (environ[i])
    {
        eq = strchr(environ[i], '=');
        if (eq)
        {
            *eq = '\0';
            printf("declare -x %s=\"%s\"\n", environ[i], eq + 1);
            *eq = '=';
        }
        else
            printf("declare -x %s\n", environ[i]);
        i++;
    }
    int j = 0;
    while (j < g_shell.exported_count)
    {
        if (!getenv(g_shell.exported_vars[j]))
            printf("declare -x %s\n", g_shell.exported_vars[j]);
        j++;
    }
}

// Print all environment variables (for env builtin)
int ft_env(char **args)
{
    extern char **environ;
    int i = 0;
    (void)args;
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return 0;
}

/*
** ft_unset - Remove environment variables
** Usage: unset VAR [VAR ...]
** Edge cases: invalid identifiers, multiple args
**this is for export just didnt have enough space in the other file
*/
int ft_unset(char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            printf("unset: not a valid identifier: %s\n", args[i]);
            i++;
            continue;
        }
        unsetenv(args[i]);
        i++;
    }
    return (0);
}