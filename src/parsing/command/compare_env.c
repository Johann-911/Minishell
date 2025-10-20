

#include "parser.h"

char	*check_for_env(t_env_list *envlst, char *str, size_t len)
{
	t_env_node	*node;

	if (!envlst || !str)
		return (NULL);
	node = envlst->head;
	while (node)
	{
		if (node->key && ft_strlen(node->key) == len && ft_strncmp(node->key,
				str, len) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

char	*expand_env(char *str, t_env_list *env_lst)
{
	size_t	i;
	int start;
	char *value;

	i = 1;
	if (!str || str[0] != '$' || !env_lst)
		return (NULL);
	if(!ft_isalpha((unsigned char)str[i]) || str[i] == '_')
		return NULL;
	start = i;
	while(str[i] && ft_isalnum((unsigned char)str[i]) || str[i] == '_')	
		i++;
	value = check_for_env(env_lst, str + start, i - start);
	if(value)
		return gc_strdup(value);
	return gc_substr("", 0, 0);
}

char	*expand_or_not(char *seg_str, t_seg_type seg_type, t_env_list *envlst,
		int last_status)
{
	int	i;

	i = 0;
	if (!seg_str)
		return (NULL);
	if (seg_type == SEG_SINGLE)
		return (seg_str);
	while (seg_str[i])
	{
		if (seg_str[i] == '$')
		{
			if(seg_str[i + 1] == '?')
				return ft_itoa(last_status);
			if(seg_type == SEG_DOUBLE || seg_type == SEG_NO_QUOTE)
				return (expand_env(seg_str, envlst));
			return (seg_str);
		}
		i++;
	}
	return seg_str;
}
