
#include "minishell.h"
#include "parser.h"





void	init_token_lst(t_token_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	lst->syntax_error = 0;
}