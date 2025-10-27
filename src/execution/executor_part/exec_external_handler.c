/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:28 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/24 16:03:39 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
/* forward declarations for static helpers defined below */
static int create_pipes(int pipes[64][2], int ncmds);
static int spawn_pipeline_children(char ***cmds, int ncmds, char **envp, int pipes[64][2], pid_t pids[64]);
static void setup_child_io_and_exec(int idx, int ncmds, int pipes[64][2], int in_fd, int out_fd, char **cmd, char **envp);
static void close_all_pipes(int pipes[64][2], int ncmds);
static int wait_children(pid_t pids[64], int ncmds);
// Searches $PATH for executable
static char *find_in_path(char *cmd)
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
    int j = 0;
    while (dirs[j])
    {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirs[j], cmd);
        if (access(fullpath, X_OK) == 0)
            return (fullpath);
        j++;
    }
    return (cmd);
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

// Executes external command (execve in current process)
void exec_external(char **args, char **envp)
{
    char *exec_path;

    exec_path = find_in_path(args[0]);
    execve(exec_path, args, envp);
}

// Sets up and runs a simple pipeline (cmd1 | cmd2)
int exec_pipeline(char ***cmds, int ncmds, char **envp)
{
    int pipes[64][2];
    pid_t pids[64];

    if (ncmds <= 0)
        return (1);
    if (create_pipes(pipes, ncmds) != 0)
        return (1);
    if (spawn_pipeline_children(cmds, ncmds, envp, pipes, pids) != 0)
    {
        close_all_pipes(pipes, ncmds);
        return (1);
    }
    close_all_pipes(pipes, ncmds);
    return wait_children(pids, ncmds);
}

static int create_pipes(int pipes[64][2], int ncmds)
{
    int i;

    i = 0;
    while (i < ncmds - 1)
    {
        if (pipe(pipes[i]) == -1)
            return (1);
        i++;
    }
    return (0);
}

static int spawn_pipeline_children(char ***cmds, int ncmds, char **envp, int pipes[64][2], pid_t pids[64])
{
    int i;

    i = 0;
    while (i < ncmds)
    {
        int in_fd = -1, out_fd = -1;
        if (setup_redirections(cmds[i], &in_fd, &out_fd))
            return (1);
        pids[i] = fork();
        if (pids[i] == 0)
        {
            setup_child_io_and_exec(i, ncmds, pipes, in_fd, out_fd, cmds[i], envp);
        }
        if (in_fd != -1)
            close(in_fd);
        if (out_fd != -1)
            close(out_fd);
        i++;
    }
    return (0);
}

static void setup_child_io_and_exec(int idx, int ncmds, int pipes[64][2], int in_fd, int out_fd, char **cmd, char **envp)
{
    int j;

    if (idx > 0)
        dup2(pipes[idx - 1][0], STDIN_FILENO);
    if (in_fd != -1)
        dup2(in_fd, STDIN_FILENO);
    if (idx < ncmds - 1)
        dup2(pipes[idx][1], STDOUT_FILENO);
    if (out_fd != -1)
        dup2(out_fd, STDOUT_FILENO);
    j = 0;
    while (j < ncmds - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    exec_external(cmd, envp);
    _exit(127);
}

static void close_all_pipes(int pipes[64][2], int ncmds)
{
    int i;

    i = 0;
    while (i < ncmds - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

static int wait_children(pid_t pids[64], int ncmds)
{
    int i;
    int status;

    status = 0;
    i = 0;
    while (i < ncmds)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 128;
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

    if (pipe(pipefd) == -1)
        return (-1);
    while (1)
    {
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        /* line ends with newline from fgets */
        if (strncmp(buffer, delimiter, strlen(delimiter)) == 0 && buffer[strlen(delimiter)] == '\n')
            break;
        write(pipefd[1], buffer, strlen(buffer));
    }
    close(pipefd[1]);
    return (pipefd[0]); /* read end */
}