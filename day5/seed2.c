#include "../include/aoc.h"
#include "part2_utils.h"
#define SEED_SIZE 2
#define MAP_SIZE 3
// test seed 2
// input seed 10

long	*store_array(char *str, int size)
{
	long *array;
	int i = 0;
	int index = 0;

	array = calloc(size, sizeof(long));
	if (!array)
		return (NULL);
	while (str[i])
	{
		array[index] = atol(str + i);
		while (isdigit(str[i]))
			i++;
		while (!isdigit(str[i]) && str[i])
			i++;
		index++;
	}
	return (array);
}

void	handle_intersects(t_seedrange **seed_ranges, long *map)
{
	t_seedrange *tmp = NULL;

	// printf("start %li range %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
	while (*seed_ranges)
	{
		// inside overlap	[===(xxx)===]
		if ((*seed_ranges)->start >= map[1] && (*seed_ranges)->start + (*seed_ranges)->range - 1 < map[1] + map[2] - 1)
		{
			inside_bounds(&tmp, (*seed_ranges)->start + map[0] - map[1], (*seed_ranges)->range);
			printf("start %li range %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
			printf("inside overlap	[===(xxx)===]\n");
		}
		
		// outside overlap	(xxx[===========]xxx)
		else if ((*seed_ranges)->start < map[1] && (*seed_ranges)->start + (*seed_ranges)->range - 1 >= map[1] + map[2] - 1)
		{
			outside_bounds(&tmp, (*seed_ranges)->start, map[1] - (*seed_ranges)->start); // left
			outside_bounds(&tmp, map[1] + map[2], (*seed_ranges)->start + (*seed_ranges)->range - map[1] + map[2]); // right
			inside_bounds(&tmp, (*seed_ranges)->start + map[0] - map[1], (*seed_ranges)->range);
			printf("start %li range %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
			printf("outside overlap	(xxx[===========]xxx)\n");
		}
		// end overlap	(xxx[xx)========]
		else if ((*seed_ranges)->start < map[1] && (*seed_ranges)->start + (*seed_ranges)->range - 1 >= map[1])
		{
			outside_bounds(&tmp, (*seed_ranges)->start, map[1] - (*seed_ranges)->start);
			inside_bounds(&tmp, (*seed_ranges)->start + map[0] - map[1], (*seed_ranges)->start + (*seed_ranges)->range - map[1]);
			printf("start %li range %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
			printf("end overlap	(xxx[xx)========]\n");
		}

		// start overlap	[========(xx]xxx)
		else if ((*seed_ranges)->start < map[1] + map[2] && (*seed_ranges)->start + (*seed_ranges)->range - 1 > map[1] + map[2] - 1)
		{
			outside_bounds(&tmp, map[1] + map[2], ((*seed_ranges)->start + (*seed_ranges)->range) - (map[1] + map[2]));
			inside_bounds(&tmp, (*seed_ranges)->start + map[0] - map[1], (map[1] + map[2]) - (*seed_ranges)->start);
			printf("start %li range %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
			printf("start overlap	[========(xx]xxx)\n");
		}
		else
		{
			append_seedrange(&tmp, new_seed_range((*seed_ranges)->start, (*seed_ranges)->range));
			printf("start %li range %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
			printf("no overlap	(xxx) [===========] (xxx)\n");
		}
		// printf("tmp start %li tmp range %li\n", tmp->start, tmp->range);
		*seed_ranges = (*seed_ranges)->next;
	}
	clear_seedrange(seed_ranges);
	// printf("tmp %li tmp %li\n", (*seed_ranges)->start, (*seed_ranges)->range);
	*seed_ranges = tmp;
}

void	check_map(t_seedrange **seed_ranges, int fd, char **str)
{
	int i = 0;
	long *map;

	while (*str && isdigit((*str)[0]))
	{
		map = store_array(*str, MAP_SIZE);
		if (!map)
			return ;
		free(*str);
		print_long_array(map, "map", MAP_SIZE);
		printf("\n");
		printf("entering handle_intersects\n\n");
		handle_intersects(seed_ranges, map);
		*str = get_next_line(fd);
	}
}

void	next_map(char **str, int fd, int times)
{
	while (times > 0)
	{
		free(*str);
		*str = get_next_line(fd);
		// printf("next map %s\n", *str);
		if (!*str)
			return ;
		times--;
	}
}

t_seedrange *store_seed_ranges(char *str)
{
	t_seedrange *seed_ranges;
	long start;
	long range;
	int i = 0;

	i = 0;
	while (str[i])
	{
		start = atol(str + i);
		while (isdigit(str[i]))
			i++;
		while (!isdigit(str[i]) && str[i])
			i++;
		range = atol(str + i);
		while (isdigit(str[i]))
			i++;
		while (!isdigit(str[i]) && str[i])
			i++;
		append_seedrange(&seed_ranges, new_seed_range(start, range));
	}
	return (seed_ranges);
}

long	lowest_location(t_seedrange *seed_ranges, long lowest)
{
	while (seed_ranges)
	{
		if (seed_ranges->start < lowest)
			lowest = seed_ranges->start;
		seed_ranges = seed_ranges->next;
	}
	return (lowest);
}

int main (int argc, char **argv)
{
	int fd;
	int i = 0;
	int index = 0;
	long lowest;
	char *str;
	t_seedrange *seedranges;
	int j = 0;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	while (1)
	{
		// initialise variables
		str = get_next_line(fd);
		if (!str)
			break ;

		// skip over seed name
		while (str[i] != ':')
			i++;
		while (!isdigit(str[i]))
			i++;
		seedranges = store_seed_ranges(str + i);
		free(str);
		str = get_next_line(fd);
		while (1)
		{
			if (!str)
				break ;
			if (str[0] == '\n')
				next_map(&str, fd, 2);
			printf("entering new map\n");
			if (str)
				check_map(&seedranges, fd, &str);
			printf("\n");
		}
		break ;
	}
	// printf("hello\n");
	lowest = lowest_location(seedranges, seedranges->start);
	printf("final %li\n", lowest);
	close(fd);
}
