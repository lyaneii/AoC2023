#include "oasis_utils.h"
#include <stdlib.h>

t_node *new_node(int *history)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	
	node->history = history;
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
		free(tmp->history);
		free(tmp);
	}
	*head = NULL;
}
