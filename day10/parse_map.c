#include "get_next_line.h"
#include "pipe_utils.h"
#include <string.h>

char	**parse_map(int fd)
{
	t_node	*head = NULL;
	t_node	*tmp;
	size_t	reference_len;
	char	**map;
	char	*str;
	int		size = 2;

	str = get_next_line(fd);
	while (str)
	{
		append_node(&head, new_node(strddup(str, '\n')));
		size++;
		free(str);
		str = get_next_line(fd);
	}
	map = calloc(size + 1, sizeof(char *));
	tmp = head;
	reference_len = strlen(tmp->str);
	map[0] = empty_row(reference_len);
	map[size - 1] = empty_row(reference_len);
	for (int i = 1; i < size - 1; i++)
	{
		map[i] = tmp->str;
		tmp = tmp->next;
	}
	clear_nodes(&head);
	return (map);
}

char	*strddup(char *str, char delimiter)
{
	char	*dup;
	int		len = 0;

	for (len = 0; str[len] && str[len] != delimiter; len++);
	dup = calloc(len + 1, sizeof(char));
	for (int i = 0; i < len; i++)
		dup[i] = str[i];
	return (dup);
}

int	find_start(char **map, char c)
{
	int	start;

	for (start = 0; !row_contains_start(map[start], c); start++);
	return (start);
}

int	row_contains_start(char *row, char c)
{
	for (int i = 0; row[i]; i++)
	{
		if (row[i] == c)
			return (1);
	}
	return (0);
}

char	*empty_row(size_t len)
{
	char *empty_row;

	empty_row = calloc(len + 1, sizeof(char));
	for (size_t i = 0; i < len; i++)
		empty_row[i] = '.';
	return (empty_row);
}
