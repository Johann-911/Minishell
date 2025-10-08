/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:54 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/26 12:35:14 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

bool	we_have_token(const char *str, int *i)
{
	int	start;

	if (!str || !str[*i] || str[*i] == ' ' || str[*i] == '\t' || str[*i] == '<'
		|| str[*i] == '>' || str[*i] == '|')
		return (false);
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<'
		&& str[*i] != '>' && str[*i] != '|')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (!is_valid_quote((char *)str, i))
				return (false);
		}
		else
			(*i)++;
	}
	return (*i > start);
}
int	scan_word(char *str, int i)
{
	int	j;

	j = i;
	if (!we_have_token(str, &j))
		return (-1);
	return (j);
}

int	scan_quote(const char *str, int i)
{
	char	q;

	if (!str || !str[i] || (str[i] != '\'' && str[i] != '\"'))
		return (-1);
	q = str[i];
	i++;
	while (str[i] && str[i] != q)
		i++;
	if (!str[i])
		return (-1);
	return (i + 1);
}

bool	is_valid_quote(char *str, int *i)
{
	char	q;

	if (!str || !str[*i] || (str[*i] != '\'' && str[*i] != '\"'))
		return (false);
	q = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != q)
		(*i)++;
	if (!str[*i])
		return (false);
	(*i)++;
	return (true);
}
