/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:28:18 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/17 16:11:49 by klejdi           ###   ########.fr       */
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
    int fd;
    if (heredoc_count == 0)
        return -1;
    last_heredoc = find_last_heredoc(cmd, heredoc_count);
    if (!last_heredoc)
        return -1;
    // TODO: Implement heredoc reading and temp file creation
    fd = open(last_heredoc->filename, O_RDONLY);
    return fd;
}
