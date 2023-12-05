#include "aoc.h"
#define SEED_SIZE 20
#define MAP_SIZE 3
// test seed 4
// input seed 20

typedef struct s_seedrange
{
	long start;
	long end;

}	t_seedrange;

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

void	convert_seeds(t_seedrange *seedrange, long *map, t_seedrange *tmp)
{
	long new_start = 0;
	long new_end = 0;

	if (seedrange->start < map[1])
		tmp->start = map[1];
	else if (seedrange->end > map[1] + map[2])
		tmp->end = map[1] + map[2];
}

void	check_map(t_seedrange **seedrange, int fd, char **str)
{
	int i = 0;
	long *map;
	t_seedrange *tmp;

	tmp = malloc(sizeof(t_seedrange));
	tmp->start = (*seedrange)->start;
	tmp->end = (*seedrange)->end;
	while (*str && isdigit((*str)[0]))
	{
		map = store_array(*str, MAP_SIZE);
		if (!map)
			return ;
		free(*str);
		print_long_array(map, "map", MAP_SIZE);
		convert_seeds((*seedrange, map, tmp);
		print_long_array(tmp, "tmp", SEED_SIZE);
		*str = get_next_line(fd);
	}
	free(*seedrange);
	*seedrange = tmp;
	// print_long_array(*seedrange, "new seeds", SEED_SIZE);
}

int	next_map(char **str, int fd, int times)
{
	while (times > 0)
	{
		free(*str);
		*str = get_next_line(fd);
		// printf("next map %s\n", *str);
		if (!*str)
			return (0);
		times--;
	}
	return (1);
}

t_seedrange **store_seed_ranges(char *str)
{
	t_seedrange **seed_ranges;
	int index = 0;
	int i = 0;

	i = 0;
	seed_ranges = calloc(SEED_SIZE / 2, sizeof(t_seedrange *));
	while (str[i])
	{
		seed_ranges[index]->start = atol(str + i);
		while (isdigit(str[i]))
			i++;
		while (!isdigit(str[i]) && str[i])
			i++;
		seed_ranges[index]->end = (seed_ranges[index]->start + atol(str + i)) - 1;
		while (isdigit(str[i]))
			i++;
		while (!isdigit(str[i]) && str[i])
			i++;
		index++;
	}
	return (seed_ranges);
}

int main (int argc, char **argv)
{
	long final = 0;
	int fd;
	int i = 0;
	int index = 0;
	char *str;
	t_seedrange **seedranges;
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
		while (index < SEED_SIZE)
		{
			if (!str)
				break ;
			if (str[0] == '\n')
				next_map(&str, fd, 2);
			check_map(&seedranges[index], fd, &str);
			printf("\n");
			index++;
		}
		break ;
	}
	final = seeds[0];
	for (int x = 0; x < SEED_SIZE; x++)
	{
		if (seeds[x] < final)
			final = seeds[x];
	}
	printf("final %li\n", final);
	close(fd);
}
