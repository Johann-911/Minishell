/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:28:18 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/22 19:35:10 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

// Counts heredoc redirections
int count_heredoc(t_commandlist *cmd)
{
    int count = 0;
    t_filelist *cur = cmd->files;
    while (cur)
    {
        if (cur->type == HEREDOC)
            count++;
        cur = cur->next;
    }
    return count;
}

// Finds the last heredoc
static t_filelist *find_last_heredoc(t_commandlist *cmd, int heredoc_count)
{
    int cur_count = 0;
    t_filelist *cur = cmd->files;
    while (cur)
    {
        if (cur->type == HEREDOC)
        {
            cur_count++;
            if (cur_count == heredoc_count)
                return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Opens the last heredoc
int setup_heredoc_fd(t_commandlist *cmd)
{
    int heredoc_count = count_heredoc(cmd);
    t_filelist *last_heredoc;
    if (heredoc_count == 0)
        return -1;
    last_heredoc = find_last_heredoc(cmd, heredoc_count);
    if (!last_heredoc)
        return -1;
    {
        char template[] = "/tmp/minishell_heredoc_XXXXXX";
        int tmpfd = mkstemp(template);
        if (tmpfd == -1)
            return -1;
        /* write heredoc content from stdin until delimiter */
        char buffer[1024];
        size_t len = strlen(last_heredoc->filename);
        while (fgets(buffer, sizeof(buffer), stdin))
        {
            if (strncmp(buffer, last_heredoc->filename, len) == 0 && buffer[len] == '\n')
                break;
            write(tmpfd, buffer, strlen(buffer));
        }
        /* reopen for reading at start */
        lseek(tmpfd, 0, SEEK_SET);
        return tmpfd;
    }
}
