#include "minishell.h"

int	red_len(char *input, int i)
{
	if (!input[i])
		return (0);
	if ((input[i] == '<' && input[i + 1] == '<') || input[i] == '>' && input[i
		+ 1] == '>')
		return 2;
	if(input[i] == '<' || input[i] == '>')
		return 1;	
	return 0;	
}
