/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:07:02 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/15 00:22:41 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
 * ft_cd - Change the current working directory.
 * Handles all edge cases:
 * - No argument: change to HOME
 * - "-": change to OLDPWD and print new dir
 * - Too many arguments: error
 * - Nonexistent directory: error
 * - Permission denied: error
 * - Updates OLDPWD and PWD in environment
 */
int ft_cd(char **args)
{
    char *target;
    char oldpwd[PATH_MAX];
    char newpwd[PATH_MAX];
    int argc = 0;
    while (args[argc])
        argc++;

    // Save current directory for OLDPWD
    if (!getcwd(oldpwd, sizeof(oldpwd)))
    {
        perror("cd: getcwd (oldpwd)");
        return 1;
    }

    // No argument: go to HOME
    if (argc == 1 || (args[1] && args[1][0] == '\0'))
    {
        target = getenv("HOME");
        if (!target)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        // "-": go to OLDPWD
        target = getenv("OLDPWD");
        if (!target)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
    }
    else
    {
        target = args[1];
    }

    // Too many arguments
    if (argc > 2)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }

    // Try to change directory
    if (chdir(target) != 0)
    {
        perror("cd");
        return 1;
    }

    // Get new working directory
    if (!getcwd(newpwd, sizeof(newpwd)))
    {
        perror("cd: getcwd (newpwd)");
        return 1;
    }

    // Print new directory if "cd -"
    if (args[1] && strcmp(args[1], "-") == 0)
        printf("%s\n", newpwd);

    // Update OLDPWD and PWD in environment
    // NOTE: setenv only updates the process environment. If your shell
    // maintains its own environment list, update OLDPWD and PWD there as well.
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", newpwd, 1);

    return 0;
}