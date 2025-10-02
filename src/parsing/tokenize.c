



#include "minishell.h"


void init_token_lst(t_token_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	lst->syntax_error = 0;
}

t_token *create_token(t_toktype type, char *val)
{
	t_token *t;

	t = gc_malloc(sizeof(*t));
	if(!t)
		return NULL;
	t->type = type;
	t->value = val;
	t->next = NULL;
	return t;
}



int push_token(t_token_list *lst, t_token *token)
{
	if(!lst || !token)
		return 0;
	if(!lst->head)
	{
		lst->head = token;
		lst->tail = token;
	}
	else
	{
		lst->tail->next = token;
		lst->tail = token;
	}
	lst->size++;
	return 1;
}

int add_token(t_token_list *lst, t_toktype type, char *str, int len)
{
	char *copy;
	t_token *tok; 
	if(!lst || !str || len <=0)
		return 0;
	copy = gc_substr(str, 0, len);
	if(!copy)
		return 0;
	tok = create_token(type, copy);
	if(!tok)
		return 0;
	return(push_token(lst, tok));
}

int tokenize(t_token_list *lst, char *input)
{
	int i;	
	int start;
	
	i = 0;
	while(input[i])
	{
		i = skip_spaces(input);
		if(!input)
			break;
		if(input[i] == '|')
			add_token(lst, TK_PIPE, input + 1, 1)
		else if(is_red())
		{
			if(red_len(input, i) == 2)
				add_token(lst, type, input+i, red_len(input, i))
			else if(red_len(input, i) == 1)
				add_token(lst, type, input+i, red_len(input, i))
			else
			{
				start = i;
				add_token
			}
		}
		i++;
	}
}
