#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard includes */
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>

/*
** --------------------------------------------------------------------------
**  Macros
** --------------------------------------------------------------------------
*/
# define STDIN_FD  0
# define STDOUT_FD 1
# define STDERR_FD 2

/*
** --------------------------------------------------------------------------
**  Environment linked list
** --------------------------------------------------------------------------
*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*
** --------------------------------------------------------------------------
**  Redirections linked list
** --------------------------------------------------------------------------
*/
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

/*
** --------------------------------------------------------------------------
**  Command linked list
** --------------------------------------------------------------------------
*/
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	bool			is_builtin;
	pid_t			pid;
	int				status;
	struct s_cmd	*next;
}	t_cmd;

/*
** --------------------------------------------------------------------------
**  File node for redirections
** --------------------------------------------------------------------------
*/
typedef struct s_file
{
	char			*filename;
	int				fd;
	struct s_file	*next;
}	t_file;

/*
** --------------------------------------------------------------------------
**  Shell context
** --------------------------------------------------------------------------
*/
typedef struct s_shell
{
	t_env	*env_list;
	char	**envp;
	int		envp_dirty;
	int		last_status;
	int		interactive;
	int		sig_received;
}	t_shell;

#endif /* MINISHELL_H */