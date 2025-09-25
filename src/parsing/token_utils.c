/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:54 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/25 18:23:37 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool is_boundary_char(char c)
{
	return(c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');	
}

bool we_have_token(const char *str, int i)
{
	int j;
	int next;
	
	j = i;
	if(!str || !str[j] || is_boundary_char(str[j]))
		return false;
	while(str && !is_boundary_char(str[j]))
	{
		if(str[j] == '\'' || str[j] == '\"')
		{
			next = scan_quote(str, j);
			if(next < 0)
				return false;
			j = next;			
		}		
		else
			j++;	
	}
	return j > i;	
}

int scan_quote(const char *str, int i)
{
	char q;
	
	if(!str || !str[i] ||(str[i] != '\'' && str[i] != '\"'))
		return -1;
	q = str[i];
	i++;
	while(str[i] && str[i] != q)
		i++;
	if(!str[i])
		return -1;
	return i + 1;

}

bool is_valid_quote(char *str, int i)
{
	if(!str || !str[i])
		return true;
	if(str[i] != '\'' && str[i] != '\"')
		return true;
	return (scan_quote(str, i) >= 0);
}
