
#include "parser.h"

bool	is_redirection(t_toktype t)
{
	return (t == TK_INFILE || t == TK_OUTFILE || t == TK_APPEND
		|| t == TK_HEREDOC);
}

int add_cmdlst(token *token, t_token_list *toklst, t_cmd_list *cmdlst)
{

	
}


char	*token_to_cmd(t_token *token, t_token_list *toklst, t_cmd_list *cmdlst)
{
	t_cmd_node	*cmdnode;
	int			i;
	int			j;
	
	i = 0;
	cmdnode = cmdlst->head;
	token = toklst->head;
	while (token)
	{
		cmdnode = create_cmdnode();
		if (!cmdnode)
		return (NULL);
		if (token->type == TK_WORD)
		cmdnode->cmd[i] = token->value;
		if (token->type == TK_PIPE)
		handle_cmd_pipe(token, toklst, cmdlst);
		token = token->next;
		i++;
	}
	return (cmdlst);
}

char	*look_for_cmd(t_token *token, t_token_list *toklst, t_cmd_list *cmdlst)
{
	t_cmd_node	*cmdnode;
	t_file_node	*filenode;

	token = toklst->head;
	while (token)
	{
		if (token->type == TK_WORD)
			cmdnode = token_to_cmd(token, toklst, cmdlst);
		if (is_redirection(token->type) && token->next->type == TK_WORD)
			filenode = create_filenode(token->value, token->type);
		if (token->type == TK_PIPE)
		
		token = token->next;
	}
	return (cmdlst);
}

void	final_token(t_token_list *toklst, t_env_list *envlst, int last_status)
{
	t_token			*token;
	t_segment_list	*seglst;
	
	if (!toklst)
	return ;
	token = toklst->head;
	while (token)
	{
		if (token->type == TK_WORD)
		{
			seglst = gc_malloc(sizeof(*seglst));
			if (!seglst)
				return ;
			init_segment_lst(seglst);
			if (find_segment(seglst, token->value))
				token->value = segments_expand(seglst, envlst, last_status);
		}
		token = token->next;
	}
}
