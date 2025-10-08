

#include "parser.h"

t_token	*create_token(t_toktype type, char *val)
{
	t_token	*t;

	t = gc_malloc(sizeof(*t));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = val;
	t->next = NULL;
	return (t);
}

int	push_token(t_token_list *lst, t_token *token)
{
	if (!lst || !token)
		return (0);
	if (!lst->head)
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
	return (1);
}

int	add_token(t_token_list *lst, t_toktype type, char *str, int len)
{
	char	*copy;
	t_token	*tok;

	if (!lst || !str || len <= 0)
		return (0);
	copy = gc_substr(str, 0, len);
	if (!copy)
		return (0);
	tok = create_token(type, copy);
	if (!tok)
		return (0);
	return (push_token(lst, tok));
}

int	handle_word(t_token_list *lst, char *input, int *i)
{
	int	next;
	int	start;

	start = i;
	while (input && input[*i] != ' ' && input[*i] != '\t' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '<')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			next = scan_quote(input, *i);
			if (next < 0)
				return (0);
			*i = next;
		}
		else
			*i++;
	}
	if (*i == start)
		return (0);
	return (add_token(lst, TK_WORD, input + start, *i - start));
}

int	tokenize(t_token_list *lst, char *input)
{
	int	i;
	int	start;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			if(!add_token(lst, TK_PIPE, input + i, 1));
				return 0;
		}
		i++;
		if (is_red(input, i))
		{
			if(!handle_redir(lst, input, i, red_len(input, i)))
				return 0;
		}
		if (!handle_word(lst, input, &i))
			return (0);
	}
	return (1);
}
