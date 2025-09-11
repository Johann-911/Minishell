#ifndef EXECUTOR_STRUCTS_H
# define EXECUTOR_STRUCTS_H

# include "minishell.h"

/*
** --------------------------------------------------------------------------
**  Pipe structure
** --------------------------------------------------------------------------
*/
typedef struct s_pipe
{
	int		read_fd;      /* read end of the pipe */
	int		write_fd;     /* write end of the pipe */
}	t_pipe;

/*
** --------------------------------------------------------------------------
**  Heredoc temp file node
** --------------------------------------------------------------------------
*/
typedef struct s_heredoc
{
	char			*tmp_filename;   /* temporary file for heredoc */
	int				fd;              /* file descriptor */
	struct s_heredoc *next;
}	t_heredoc;

/*
** --------------------------------------------------------------------------
**  Executor command node
**  Extends t_cmd from minishell.h with runtime info
** --------------------------------------------------------------------------
*/
typedef struct s_exec_cmd
{
	t_cmd			*cmd;         /* pointer to general command struct */
	pid_t			pid;          /* child PID if forked */
	int				stdin_fd;     /* saved stdin for redirections */
	int				stdout_fd;    /* saved stdout for redirections */
	int				exit_status;  /* exit status after execution */
	struct s_exec_cmd *next;
}	t_exec_cmd;

/*
** --------------------------------------------------------------------------
**  Executor context
**  Stores info about the pipeline being executed
** --------------------------------------------------------------------------
*/
typedef struct s_exec_ctx
{
	t_exec_cmd	*cmd_list;       /* linked list of commands in the pipeline */
	t_pipe		*pipes;          /* array of pipes if multiple commands */
	int			num_cmds;        /* number of commands in pipeline */
	t_shell		*shell;          /* pointer to shell context */
	t_heredoc	*heredocs;       /* linked list of prepared heredoc files */
}	t_exec_ctx;

#endif /* EXECUTOR_STRUCTS_H */
