#include "get_next_line.h"
#include "cosmic_utils.h"
#include <stdlib.h>

static void	free_2d_array(char **ptr)
{
	for (int i = 0; ptr[i]; i++)
		free(ptr[i]);
	free(ptr);
	ptr = NULL;
}

t_map	*parse_map(int fd, int **expand_rows, int **expand_columns)
{
	t_map	*galaxy;
	t_map	*tmp = NULL;
	t_map	*expansions = NULL;
	char	**map;
	char	*str;
	int		size = 0;

	str = get_next_line(fd);
	while (str)
	{
		append_map(&tmp, new_map(str, 0, 0));
		size++;
		str = get_next_line(fd);
	}

	map = tmp_map(tmp, size);
	check_expansions(map, &expansions);
	*expand_rows = parse_row_expansions(expansions);
	*expand_columns = parse_column_expansions(expansions);
	galaxy = galaxy_coords(map);

	free_2d_array(map);
	clear_map(&expansions);
	clear_map(&tmp);
	return (galaxy);
}

char	**tmp_map(t_map *tmp, int size)
{
	char	**map;

	map = calloc(size + 1, sizeof(char *));
	for (int i = 0; i < size; i++)
	{
		map[i] = tmp->str;
		tmp = tmp->next;
	}
	return (map);
}

void	check_expansions(char **map, t_map **expansions)
{
	int	row, column;

	for (row = 0; map[row]; row++)
	{
		if (!row_has_galaxy(map[row]))
			append_map(expansions, new_map(NULL, row, -1));
	}
	for (column = 0, row = 0; map[row][column]; column++)
	{
		if (!column_has_galaxy(map, row, column))
			append_map(expansions, new_map(NULL, -1, column));
	}
}

int	row_has_galaxy(char *row)
{
	for (int i = 0; row[i]; i++)
	{
		if (row[i] == '#')
			return (1);
	}
	return (0);
}

int	column_has_galaxy(char **map, int row, int column)
{
	while (map[row])
	{
		if (map[row][column] == '#' || map[row][column] == '\n')
			return (1);
		row++;
	}
	return (0);
}

int	*parse_row_expansions(t_map *expansions)
{
	int	size = expansion_amount(expansions, 'r');
	int *row_expansions = calloc(size + 1, sizeof(int));
	int	i = 0;

	while (expansions && expansions->column == -1)
	{
		row_expansions[i++] = expansions->row;
		expansions = expansions->next;
	}
	row_expansions[i] = -1;
	return (row_expansions);
}

int	*parse_column_expansions(t_map *expansions)
{
	int	size = expansion_amount(expansions, 'c');
	int *column_expansions = calloc(size + 1, sizeof(int));
	int	i = 0;

	while (expansions && expansions->column == -1)
		expansions = expansions->next;
	while (expansions && expansions->row == -1)
	{
		column_expansions[i++] = expansions->column;
		expansions = expansions->next;
	}
	column_expansions[i] = -1;
	return (column_expansions);
}

int	expansion_amount(t_map *expansions, const char check)
{
	int	size = 0;

	if (check == 'r')
	{
		while (expansions && expansions->column == -1)
		{
			size++;
			expansions = expansions->next;
		}
	}
	else if (check == 'c')
	{
		while (expansions && expansions->column == -1)
			expansions = expansions->next;
		while (expansions && expansions->row == -1)
		{
			size++;
			expansions = expansions->next;
		}
	}
	return (size);
}

t_map	*galaxy_coords(char **map)
{
	t_map	*galaxy = NULL;

	for (int row = 0; map[row]; row++)
	{
		for (int column = 0; map[row][column]; column++)
		{
			if (map[row][column] == '#')
				append_map(&galaxy, new_map(NULL, row, column));
		}
	}
	return (galaxy);
}