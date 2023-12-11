#include "aoc.h"
#include "cosmic_utils.h"

int main (int argc, char **argv)
{
	t_map	*galaxy;
	t_map	*current_galaxy;
	size_t	sum;
	int		fd;
	int		*expand_rows, *expand_columns;
	int		expansion_size;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	galaxy = parse_map(fd, &expand_rows, &expand_columns);

	sum = 0;
	current_galaxy = galaxy;
	expansion_size = 2;
	while (current_galaxy)
	{
		sum += connect_galaxies(current_galaxy, expand_rows, expand_columns, expansion_size);
		current_galaxy = current_galaxy->next;
	}
	printf("part 1 = %li\n", sum);

	sum = 0;
	current_galaxy = galaxy;
	expansion_size = 1000000;
	while (current_galaxy)
	{
		sum += connect_galaxies(current_galaxy, expand_rows, expand_columns, expansion_size);
		current_galaxy = current_galaxy->next;
	}
	printf("part 2 = %li\n", sum);

	// cleanup
	clear_map(&galaxy);
	free(expand_rows);
	free(expand_columns);
	close(fd);
}

size_t	connect_galaxies(t_map *current, int *expand_rows, int *expand_columns, int size)
{
	t_map	*rest = current->next;
	size_t	sum = 0;
	int		row_diff, column_diff;

	size--;
	while (rest)
	{
		row_diff = abs(rest->row - current->row);
		column_diff = abs(rest->column - current->column);
		sum += expansions_in_range(rest->row, current->row, expand_rows, size);
		sum += expansions_in_range(rest->column, current->column, expand_columns, size);
		sum += row_diff + column_diff;
		rest = rest->next;
	}
	return (sum);
}

int	expansions_in_range(int start, int end, int *expansion, int expansion_size)
{
	int	i = 0;
	int	amount = 0;
	int flip;
	
	if (end < start)
	{
		flip = start;
		start = end;
		end = flip;
	}
	while (expansion[i] != -1)
	{
		if (expansion[i] > start && expansion[i] < end)
			amount += expansion_size;
		i++;
	}
	return (amount);
}