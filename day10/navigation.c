#include "pipe_utils.h"

Nav	evaluate_from_start(char **map, int row, int pos)
{
	if (map[row - 1][pos] == 'F' || map[row - 1][pos] == '7' || map[row - 1][pos] == '|')
		return (NORTH);
	if (map[row][pos + 1] == 'J' || map[row][pos + 1] == '7' || map[row][pos + 1] == '-' )
		return (EAST);
	if (map[row + 1][pos] == 'L' || map[row + 1][pos] == 'J' || map[row + 1][pos] == '|')
		return (SOUTH);
	if (pos > 0 && (map[row][pos - 1] == 'F' || map[row][pos - 1] == 'L' || map[row][pos - 1] == '-' ))
		return (WEST);
	return (6);
}

Nav	evaluate_north(char current_pos)
{
	if (current_pos == '|')
		return (NORTH);
	if (current_pos == 'F')
		return (EAST);
	if (current_pos == '7')
		return (WEST);
	return (INVALID);
}

Nav	evaluate_east(char current_pos)
{
	if (current_pos == 'J')
		return (NORTH);
	if (current_pos == '-')
		return (EAST);
	if (current_pos == '7')
		return (SOUTH);
	return (INVALID);
}

Nav	evaluate_south(char current_pos)
{
	if (current_pos == 'L')
		return (EAST);
	if (current_pos == '|')
		return (SOUTH);
	if (current_pos == 'J')
		return (WEST);
	return (INVALID);
}

Nav	evaluate_west(char current_pos)
{
	if (current_pos == 'L')
		return (NORTH);
	if (current_pos == 'F')
		return (SOUTH);
	if (current_pos == '-')
		return (WEST);
	return (INVALID);
}

void	take_step(char **map, int *row, int *column, Nav direction, char fill)
{
	if (map[*row][*column] != 'S')
		map[*row][*column] = fill;
	if (direction == NORTH)
		(*row)--;
	else if (direction == EAST)
		(*column)++;
	else if (direction == SOUTH)
		(*row)++;
	else
		(*column)--;
}
