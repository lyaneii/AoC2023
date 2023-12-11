#include "aoc.h"
#include "pipe_utils.h"

int	main (int argc, char **argv)
{
	char	**map, **loop_map;
	char	fill = '*';
	int		fd;
	int		start_row, distance, nest_size;

	nest_size = 0;
	printf("%d\n", nest_size);
	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	// parse map and duplicate map for part 2
	map = parse_map(fd);
	loop_map = duplicate_map(map);
	
	// part 1
	start_row = find_start(map, 'S');
	distance = traverse_loop(map, start_row, fill);

	// part 2
	fill_non_loop_areas(map, loop_map, fill);
	nest_size = evaluate_enclosed_areas(loop_map, fill);
	for (int i = 0; loop_map[i]; i++)
		printf("%s\n", loop_map[i]);
	
	printf("\npart 1 = %d\n", distance);
	printf("\npart 2 = %d\n", nest_size);

	free_2d_array(loop_map);
	free_2d_array(map);
	close(fd);
}

int	traverse_loop(char **map, int start_row, char fill)
{
	int		distance, row, column;
	int		loop_found = 0;
	Nav		direction = START;

	for (column = 0; map[start_row][column] != 'S'; column++);
	row = start_row;
	distance = 0;

	while (loop_found != 1)
	{
		direction = determine_direction(map, row, column, direction);
		take_step(map, &row, &column, direction, fill);
		distance++;
		if (map[row][column] == 'S')
		{
			map[row][column] = fill;
			loop_found = 1;
		}
	}
	return (distance / 2);
}

Nav	determine_direction(char **map, int row, int column, Nav previous)
{
	switch (previous)
	{
		case START:
			return (evaluate_from_start(map, row, column));
		case NORTH:
			return (evaluate_north(map[row][column]));
		case EAST:
			return (evaluate_east(map[row][column]));
		case SOUTH:
			return (evaluate_south(map[row][column]));
		case WEST:
			return (evaluate_west(map[row][column]));
		case INVALID:
			break ;
	}
	return (INVALID);
}
