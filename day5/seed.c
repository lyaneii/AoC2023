#include "aoc.h"
#define SEED_SIZE 20
#define MAP_SIZE 3
// test seed 4
// input seed 20

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

void	convert_seeds(long *seeds, long *map, long *tmp)
{
	int i = 0;

	while (i < SEED_SIZE)
	{
		if (seeds[i] >= map[1] && seeds[i] < (map[1] + map[2]))
			tmp[i] = map[0] + seeds[i] - map[1];
		i++;
	}
}

void	check_map(long **seeds, int fd, char **str)
{
	int i = 0;
	long *map;
	long *tmp;

	tmp = calloc(SEED_SIZE, sizeof(long));
	memcpy(tmp, *seeds, SEED_SIZE * sizeof(long));
	while (*str && isdigit((*str)[0]))
	{
		map = store_array(*str, MAP_SIZE);
		if (!map)
			return ;
		free(*str);
		print_long_array(map, "map", MAP_SIZE);
		convert_seeds(*seeds, map, tmp);
		print_long_array(tmp, "tmp", SEED_SIZE);
		*str = get_next_line(fd);
	}
	free(*seeds);
	*seeds = tmp;
	print_long_array(*seeds, "new seeds", SEED_SIZE);
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

int main (int argc, char **argv)
{
	long final = 0;
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
		str = get_next_line(fd);
		while (str)
		{
			if (!str)
				break ;
			if (str[0] == '\n')
				next_map(&str, fd, 2);
			check_map(&seeds, fd, &str);
			printf("\n");
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
