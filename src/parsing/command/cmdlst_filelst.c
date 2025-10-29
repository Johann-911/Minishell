#include "parser.h"

t_cmd_node	*create_cmdnode(void)
{
	t_cmd_node	*cmdnode;

	cmdnode = gc_malloc(sizeof(*cmdnode));
	if (!cmdnode)
		return (NULL);
	cmdnode->cmd_type = CMD;
	cmdnode->cmd = NULL;
	return (cmdnode);
}

t_file_node	*create_filenode(char *str, int red_type)
{
	t_file_node	*filenode;

	filenode = gc_malloc(sizeof(*filenode));
	if (!filenode)
		return (NULL);
	filenode->redir_type = red_type;
	filenode->filename = str;
	return (filenode);
}

void	push_cmd(t_cmd_list *lst, t_cmd_node *node)
{
	if (!lst || !node)
		return ;
	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	lst->size++;
}

void	push_file(t_file_list *lst, t_file_node *node)
{
	if (!lst || !node)
		return ;
	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	lst->size++;
}