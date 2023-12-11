#include "pipe_utils.h"

int	evaluate_enclosed_areas(char **map, char fill)
{
	int	nest_size = 0;

	for (int row = 0; map[row]; row++)
		nest_size += evaluate_row(map[row], fill);
	return (nest_size);
}

int	evaluate_row(char *row, char fill)
{
	int	nest_size = 0;
	int	column = 0;
	int	pipes_amount = 2;

	while (row[column] == fill)
		column++;
	while (row[column])
	{
		pipes_amount += evaluate_pipes(row, &column);
		if (pipes_amount % 2 == 1)
		{
			while (row[column] == fill)
			{
				row[column] = '@';
				column++;
				nest_size++;
			}
		}
		else
		{
			while (row[column] == fill)
				column++;
		}
	}
	return (nest_size);
}

int	evaluate_pipes(char *row, int *column)
{
	if (row[*column] == 'F')
	{
		(*column)++;
		while (row[*column] == '-')
			(*column)++;
		if (row[*column] == 'J')
		{
			(*column)++;
			return (1);
		}
		(*column)++;
		return (2);
	}
	if (row[*column] == 'L')
	{
		(*column)++;
		while (row[*column] == '-')
			(*column)++;
		if (row[*column] == '7')
		{
			(*column)++;
			return (1);
		}
		(*column)++;
		return (2);
	}
	(*column)++;
	return (1);
}
