/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:16:35 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/25 18:19:57 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool is_vailid_red(char *str, int i)
{
	while(str[i]== ' ' || str[i] == '\t')
		i++;
	if(str[i] == '\0' || str[i] == '<' || str[i] == '>' || str[i] == '|')
		return false;
	return true;	
}

bool is_red(char *str, int i)
{

	if(str[i] == '<' && str[i + 1] == '<')
		return(is_vailid_red(str, i + 2));	
	else if(str[i] == '>' && str[i + 1] == '>')
		return(is_vailid_red(str, i + 2));
	else if(str[i] == '<')
		return(is_vailid_red(str, i +1)); 
	else if(str[i] == '>')
		return(is_vailid_red(str, i + 1));	
	return false;
}

bool is_valid_pipe(char *str, int i)
{
	i++;
	while(str[i] == ' ' || str[i]  == '\t')
		i++;
	if(str[i] == '\0' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		return false;	
	return true;	
}

bool check_tokens(char *str)
{
	int i;

	i = 0;
	if(!str)
		return false;
	while(str[i])
	{
		while(str[i] == ' ' || str[i]  == '\t')
			i++;
		if(str[i] == '|' && !is_valid_pipe(str, i))
			return false;
		else if(!is_red(str[i], i) && str[i] == '<' || str[i] == '>')
			return false;
		else if(str[i] ==  '\'' || str[i] == '\"')
		{
			if(!is_vailid_quote(str, i));
				return false;
		}
		else if(!we_have_token(str, i));
			return false;
		i++;
	}
	return true;	
}
 