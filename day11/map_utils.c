#include "cosmic_utils.h"
#include <stdlib.h>

t_map	*new_map(char *str, int row, int column)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	
	map->str = str;
	map->row = row;
	map->column = column;
	map->next = NULL;

	return (map);
}

t_map	*last_map(t_map *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	append_map(t_map **head, t_map *new_map)
{
	if (!*head)
		*head = new_map;
	else
		last_map(*head)->next = new_map;
}

void	clear_map(t_map **head)
{
	t_map	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	*head = NULL;
}
