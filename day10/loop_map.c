#include "pipe_utils.h"

char	**duplicate_map(char **map)
{
	char	**dup_map;
	int		i, size;

	for (size = 0; map[size]; size++);
	dup_map = malloc((size + 1) * sizeof(char *));
	for (i = 0; map[i]; i++)
		dup_map[i] = strddup(map[i], '\0');
	dup_map[i] = NULL;
	return (dup_map);
}

void	invert_row(char *filled_row, char *inv_row, char fill)
{
	for (int i = 0; inv_row[i]; i++)
	{
		while (filled_row[i] == fill)
			i++;
		inv_row[i] = fill;
	}
}

void	fill_non_loop_areas(char **filled_map, char **loop_map, char fill)
{
	for (int i = 0; loop_map[i]; i++)
	{
		if (row_contains_start(loop_map[i], 'S'))
			close_loop_char(loop_map, i, 'S');
		invert_row(filled_map[i], loop_map[i], fill);
	}
}

void	close_loop_char(char **map, int row, char fill)
{
	int	column;

	for (column = 0; map[row][column] != fill; column++);
	map[row][column] = determine_loop_connection(map, row, column);
}

char	determine_loop_connection(char **map, int row, int pos)
{
	switch (evaluate_from_start(map, row, pos))
	{
		case NORTH:
			if (evaluate_east(map[row][pos + 1]) != INVALID)
				return ('L');
			else if (evaluate_south(map[row + 1][pos]) != INVALID)
				return ('|');
			else
				return ('J');
		case EAST:
			if (evaluate_north(map[row - 1][pos]) != INVALID)
				return ('L');
			else if (evaluate_south(map[row + 1][pos]) != INVALID)
				return ('F');
			else
				return ('-');
		case SOUTH:
			if (evaluate_north(map[row - 1][pos]) != INVALID)
				return ('|');
			else if (evaluate_east(map[row][pos + 1]) != INVALID)
				return ('F');
			else
				return ('7');
		case WEST:
			if (evaluate_north(map[row - 1][pos]) != INVALID)
				return ('L');
			else if (evaluate_east(map[row][pos + 1]) != INVALID)
				return ('-');
			else
				return ('7');
		default:
			break ;
	}
	return (0);
}
