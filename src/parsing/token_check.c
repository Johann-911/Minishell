/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:16:35 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/23 14:20:10 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int valid_token( )
{



	
}
bool is_vailid_red(char *str, int i)
{
	while(&str)
	{
		if(&str)


	}



	
}
bool is_red(char *str, int i)
{
	int start;
	while(str[i])
	{
		if(str[i] == '<')
			return(is_vailid_red(str[i], i));	
		else if(str[i] == '>')
			return(is_vailid_red(str[i], i));
		else if(str[i] == '<' && str[i + 1] == '<')
			return(is_vailid_red(str[i], i)); 
		else if(str[i] == '>' && str[i + 1] == '>')
			return(is_vailid_red(str[i], i));	
		else 
			break;
		i++;
	}
	return false;

	
}

bool is_valid_pipe(char *str, int i)
{
	while(str[i])
	{	
		while(str[i] == ' ' || str[i]  == '/t')
			i++;
		if(str[i] != ' ' || str[i]  != '/t')
			return true;	
	}
	return false;	
}

bool check_tokens(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		while(str[i] == ' ' || str[i]  == '/t')
			i++;
		while(str[i] != ' ' || str[i]  != '/t')
		{
			if(str[i] == '|')
				return(is_valid_pipe(str[i], i));
			else if(is_red(str[i], i))
				return(is_valid_red(str[i], i));
			else if(is_quote(str[i], i))
				return(is_vailid_quote(str[i], i));
			else
				we_have_token(str[i], i);
			i++;	 
		}
		
	}
	return false;	
}
-    < 