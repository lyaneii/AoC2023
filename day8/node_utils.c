#include "maps.h"
#include <string.h>
#include <stdlib.h>

t_node *new_node(char *current_map)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	
	new_node->current_map = current_map;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->link = NULL;

	return (new_node);
}

t_node	*last_node(t_node *head)
{
	while (head->link)
		head = head->link;
	return (head);
}

void	append_node(t_node **head, t_node *new_node)
{
	if (!*head)
		*head = new_node;
	else
		last_node(*head)->link = new_node;
}

void	clear_maps(t_node **head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->link;
		free(tmp->current_map);
		free(tmp);
	}
	*head = NULL;
}

int	maps_size(t_node *head)
{
	int	size = 0;

	while (head)
	{
		size++;
		head = head->link;
	}
	return (size);
}

t_node	*start_position(t_node *head, const char *to_find, int offset)
{
	int	len = 0;

	while (to_find[len])
		len++;
	while (strncmp(head->current_map + offset, to_find, len))
		head = head->link;
	return (head);
}