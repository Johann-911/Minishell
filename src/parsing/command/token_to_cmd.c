
#include "parser.h"

t_segment *create_segment(char *start, int len, t_seg_type type)
{
	t_segment *segment;

	segment = gc_malloc(sizeof(*segment));
	if(!segment)
		return NULL;
	segment->value = gc_substr(start, 0, (size_t)len);
	if(!segment->value)
		return NULL;
	segment->type = type;
	segment->next = NULL; 
	return segment;
}


int push_segment(t_segment_list *lst, t_segment *segment)
{
	if(!lst || !segment)
		return 0;
	if (!lst->head)
	{
		lst->head = segment;
		lst->tail = segment;
	}
	else
	{
		lst->tail->next = segment;
		lst->tail = segment;
	}
	lst->size++;
	return (1);
}

