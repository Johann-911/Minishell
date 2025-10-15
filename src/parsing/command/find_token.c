




#include "parser.h"

static int no_quote_segment(t_segment_list *lst, char *str, int *i)
{
	int start;
	t_segment *segment;

	start = *i;
	while(str[*i] && str[*i] != '\'' && str[*i] != '\"' && str[*i] != ' ')
		(*i)++;
	if(*i > start)
	{
		segment = create_segment(str + start, i - start, SEG_NO_QUOTE);
		if(!segment || !push_segment(lst, segment))
		return 0;	
	}
	return 1;
}

static int quote_segment(t_segment_list *lst, char *str, int *i)
{
	char q;
	int start;
	t_segment *segment;

	if(!str[*i] || str[*i] == '\'' || str[*i] != '\"')
		return 1;
	q == str[(*i)]++;
	start == (*i);
	while(str[*i] && str[*i] != q)
		(*i)++;
	if(!str[*i])
		return 0;
	if(q == '\'')
		segment->type == S_QUOTES;
	segment->type == D_QUOTES;
	segment = create_segment(str + q, i - q, segment->type);
	if(!segment || !push_segment(lst, segment))
		return 0;
	(*i)++;
	return 1;
}


int find_segment(t_segment_list *lst, char *str)
{
	int i;

	i = 0;
	if(!str || !lst)
		return 0;
	while(str[i])
	{
		if(!no_quote_segment(lst, str, &i))
			return 0;
		if(!str[i])
			return 0;
		if(!quote_segment(lst, str, &i))
			return 0;
	}
	return 1;
}

