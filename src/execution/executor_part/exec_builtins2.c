/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:31:20 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/15 19:51:00 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
// Helper to strip quotes from value (for export)
static char *strip_quotes(const char *value)
{
    int len = strlen(value);
    if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"') || (value[0] == '\'' && value[len - 1] == '\'')))
    {
        char *stripped = (char *)malloc(len - 1);
        if (stripped)
        {
            strncpy(stripped, value + 1, len - 2);
            stripped[len - 2] = '\0';
        }
        return stripped;
    }
    return NULL;
}

/*
** ft_export - Add or update environment variables
** Handles:
**   export VAR=value
**   export VAR
**   export (prints all env if no args)
** Edge cases: invalid identifiers, multiple args, no '='
*/

/*
** Checks if a string is a valid environment variable name
*/
int is_valid_identifier(const char *name)
{
    int i;

    if (!name || !(name[0] == '_' || (name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z')))
        return (0);
    i = 1;
    while (name[i])
    {
        if (!(name[i] == '_' || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] >= '0' && name[i] <= '9')))
            return (0);
        i++;
    }
    return (1);
}

// Checks if a variable is already in exported list
static int is_in_exported(const char *name)
{
    int i = 0;
    while (i < g_shell.exported_count)
    {
        if (strcmp(g_shell.exported_vars[i], name) == 0)
            return 1;
        i++;
    }
    return 0;
}

/*
** Prints all exported environment variables in bash format
*/
// Prints all exported environment variables in bash format (<=25 lines)
static void print_exported_env(void)
{
    extern char **environ;
    int i = 0;
    char *eq;
    // Print all environment variables
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
    // Print exported-but-unset variables
    int j = 0;
    while (j < g_shell.exported_count)
    {
        if (!getenv(g_shell.exported_vars[j]))
            printf("declare -x %s\n", g_shell.exported_vars[j]);
        j++;
    }
}

/*
** ft_export - Add or update environment variables with full edge case handling
*/
// Add or update environment variables (<=25 lines)

static void export_with_value(char *arg)
{
    char *eq;
    char *value;
    char *stripped;
    eq = strchr(arg, '='); // first occurrence of '='
    /*
    ** Validate only the variable name (before '=') for export.
    ** Temporarily replace '=' with '\0' to isolate the name, validate, then restore '='.
    */
    *eq = '\0';
    if (!is_valid_identifier(arg))
        printf("export: not a valid identifier: %s\n", arg);
    else
    {
        value = eq + 1;
        stripped = strip_quotes(value);
        if (stripped)
        {
            setenv(arg, stripped, 1);
            free(stripped);
        }
        else
            setenv(arg, value, 1);
    }
    *eq = '='; // Restore '=' after validation and setting
}

static void export_no_value(char *arg)
{
    if (!is_valid_identifier(arg))
        printf("export: not a valid identifier: %s\n", arg);
    else if (!getenv(arg))
    {
        if (!is_in_exported(arg) && g_shell.exported_count < MAX_EXPORTED)
            g_shell.exported_vars[g_shell.exported_count++] = strdup(arg);
    }
}

int ft_export(char **args)
{
    int i;
    i = 1;
    if (!args[1])
    {
        print_exported_env();
        return 0;
    }
    while (args[i])
    {
        if (strchr(args[i], '='))
            export_with_value(args[i]);
        else
            export_no_value(args[i]);
        i++;
    }
    return 0;
}
