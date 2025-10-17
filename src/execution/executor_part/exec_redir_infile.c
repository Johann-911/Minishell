/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_infile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klejdi <klejdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:25:42 by klejdi            #+#    #+#             */
/*   Updated: 2025/10/16 18:02:31 by klejdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

// Counts infile/heredoc redirections
int count_infile(t_commandlist *cmd)
{
    int count = 0;
    t_filelist *cur = cmd->files;
    while (cur)
    {
        if (cur->type == INFILE || cur->type == HEREDOC)
            count++;
        cur = cur->next;
    }
    return count;
}

// Finds the last infile/heredoc
static t_filelist *find_last_infile(t_commandlist *cmd, int infile_count)
{
    int cur_count = 0;
    t_filelist *cur = cmd->files;
    while (cur)
    {
        if (cur->type == INFILE || cur->type == HEREDOC)
        {
            cur_count++;
            if (cur_count == infile_count)
                return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Opens the last infile and returns fd
int setup_infile_fd(t_commandlist *cmd)
{
    int infile_count = count_infile(cmd);
    t_filelist *last_infile;
    int fd;
    if (infile_count == 0)
        return -1;
    last_infile = find_last_infile(cmd, infile_count);
    if (!last_infile)
        return -1;
    fd = open(last_infile->filename, O_RDONLY);
    return fd;
}
