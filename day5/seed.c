#include "aoc.h"
#define SEED_SIZE 4
#define MAP_SIZE 3

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

void	convert_seeds(long *seeds, long *map)
{
	int i = 0;

	while (i < SEED_SIZE)
	{
		if (seeds[i] >= map[1] && seeds[i] < (map[1] + map[2]))
			seeds[i] = map[0] + seeds[i] - map[1];
		i++;
	}
}

void	check_map(long *seeds, int fd, char *str)
{
	int i = 0;
	long *map;
	
	while (isdigit(str[0]))
	{
		while (i < SEED_SIZE)
		{
			map = store_array(str, MAP_SIZE);
			free(str);
			print_long_array(map, "map", MAP_SIZE);
			if (!map)
				return ;
			convert_seeds(seeds + i, map);
			print_long_array(seeds, "seeds", SEED_SIZE);
			str = get_next_line(fd);
			i++;
		}
	}
}

int	next_map(char *str, int fd, int times)
{
	while (times > 0)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			return (0);
		times--;
	}
	return (1);
}

int main (int argc, char **argv)
{
	int fd;
	int i = 0;
	char *str;
	long *seeds;
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
		while (str[i] != ':')
			i++;
		while (!isdigit(str[i]))
			i++;
		seeds = store_array(str + i, SEED_SIZE);
		print_long_array(seeds, "initial seeds", SEED_SIZE);
		if (!seeds)
			return (free(str), -1);
		str = get_next_line(fd);
		while (j < 4)
		{
			if (str[0] == '\n')
				next_map(str, fd, 2);
			if (!str)
				break ;
			check_map(seeds, fd, str);
			printf("checked\n");
			j++;
		}
	}
	close(fd);
}
