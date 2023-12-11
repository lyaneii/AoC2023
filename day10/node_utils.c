#include "pipe_utils.h"

t_node	*new_node(char *str)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	
	node->str = str;
	node->next = NULL;

	return (node);
}

t_node	*last_node(t_node *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	append_node(t_node **head, t_node *new_node)
{
	if (!*head)
		*head = new_node;
	else
		last_node(*head)->next = new_node;
}

void	clear_nodes(t_node **head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	*head = NULL;
}
