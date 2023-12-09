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

void	reverse_data(t_node *data)
{
	while (data)
	{
		reverse_array(data->history, SIZE);
		data = data->next;
	}
}

void	reverse_array(int *array, int size)
{
	int	tmp;

	for (int i = 0; i < size / 2; i++)
	{
		tmp = array[i];
		array[i] = array[size - i - 1];
		array[size - i - 1] = tmp;
	}
}
