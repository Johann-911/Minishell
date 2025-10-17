/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:28 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/16 17:43:33 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
// Searches $PATH for executable
static char *find_in_path(char *cmd, char **envp)
{
    char *path = getenv("PATH");
    char *dirs[64];
    static char fullpath[512];
    int i = 0;

    if (!path)
        return (cmd);
    char *p = strtok(path, ":");
    while (p && i < 63)
    {
        dirs[i++] = p;
        p = strtok(NULL, ":");
    }
    dirs[i] = NULL;
    for (int j = 0; dirs[j]; j++)
    {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirs[j], cmd);
        if (access(fullpath, X_OK) == 0)
            return (fullpath);
    }
    return (cmd);
}

// Sets up infile and outfile redirections
static void setup_redirections(int in_fd, int out_fd)
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
}

// Convert environment list to char ** array for execve
char **convert_env_to_array(t_env_list *env_list)
{
    char **env_array;
    t_env_node *current;
    int i;
    char *temp;

    if (!env_list)
        return (NULL);
    env_array = gc_malloc(sizeof(char *) * (env_list->size + 1));
    if (!env_array)
        return (NULL);
    current = env_list->head;
    i = 0;
    while (current)
    {
        temp = ft_strjoin(current->type, "=");
        env_array[i] = ft_strjoin(temp, current->value);
        gc_free(temp);
        current = current->next;
        i++;
    }
    env_array[i] = NULL;
    return (env_array);
}

// Executes external command (fork, execve, error handling)
int exec_external(char **args, int in_fd, int out_fd, char **envp)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        setup_redirections(in_fd, out_fd);
        char *exec_path = find_in_path(args[0], envp);
        execve(exec_path, args, envp);
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
        return (WEXITSTATUS(status));
    }
    perror("fork");
    return (1);
}

// Sets up and runs a simple pipeline (cmd1 | cmd2)
int exec_pipeline(char **cmd1_args, char **cmd2_args, char **envp)
{
    int pipefd[2];
    pid_t pid1, pid2;
    pipe(pipefd);
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(cmd1_args[0], cmd1_args, envp);
        _exit(127);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        execve(cmd2_args[0], cmd2_args, envp);
        _exit(127);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

// Sets up redirections for builtins and runs them
int exec_builtin_with_redir(int (*builtin)(char **), char **args, int in_fd, int out_fd)
{
    int saved_in = dup(STDIN_FILENO);
    int saved_out = dup(STDOUT_FILENO);
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
    int ret = builtin(args);
    dup2(saved_in, STDIN_FILENO);
    dup2(saved_out, STDOUT_FILENO);
    close(saved_in);
    close(saved_out);
    return ret;
}

// Handles heredoc input (stub, expand as needed)
int exec_heredoc(const char *delimiter)
{
    char buffer[1024];
    int pipefd[2];
    pipe(pipefd);
    while (fgets(buffer, sizeof(buffer), stdin))
    {
        if (strncmp(buffer, delimiter, strlen(delimiter)) == 0 && buffer[strlen(delimiter)] == '\n')
            break;
        write(pipefd[1], buffer, strlen(buffer));
    }
    close(pipefd[1]);
    return pipefd[0]; // Return read end for use as infile
}