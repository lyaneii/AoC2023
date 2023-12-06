#include "aoc.h"
#define RACES 3

int *store_array(char *str);
long combine_into_long(char *str);
long calculate_ways(long time, long distance);

int main (int argc, char **argv)
{
	int fd;
	int *time;
	int *distance;
	long part2_time;
	long part2_distance;
	int i = 0;
	long ways = 1;
	char *str;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	// get time
	str = get_next_line(fd);
	while (!isdigit(str[i]))
		i++;
	time = store_array(str + i);
	part2_time = combine_into_long(str + i);
	free(str);

	// get distance
	str = get_next_line(fd);
	i = 0;
	while (!isdigit(str[i]))
		i++;
	distance = store_array(str + i);
	part2_distance = combine_into_long(str + i);
	free(str);

	// calculate ways
	for (int x = 0; x < RACES; x++)
		ways *= calculate_ways(time[x], distance[x]);
	printf("part 1 %li\n", ways);

	ways = calculate_ways(part2_time, part2_distance);
	printf("part 2 %li\n", ways);

	free(time);
	free(distance);
	close(fd);
}

int *store_array(char *str)
{
	int i = 0;
	int index = 0;
	int *array = calloc(RACES, sizeof(int));
	if (!array)
		return (exit(EXIT_FAILURE), NULL);

	while (index < RACES)
	{
		while (!isdigit(str[i]))
			i++;
		array[index] = atoi(str + i);
		while (isdigit(str[i]))
			i++;
		index++;
	}
	return (array);
}

long combine_into_long(char *str)
{
	int i = 0;
	long nbr = 0;

	while (str[i])
	{
		while (isdigit(str[i]))
		{
			nbr *= 10;
			nbr += str[i] - '0';
			i++;
		}
		while (!isdigit(str[i]) && str[i])
			i++;
	}
	return (nbr);
}

long calculate_ways(long time, long distance)
{
	long ways = 0;

	for (int i = 1; i < time; i++)
	{
		if (i * (time - i) > distance)
			ways++;
	}
	return (ways);
}
