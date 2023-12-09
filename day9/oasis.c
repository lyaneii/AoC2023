#include "aoc.h"
#include "oasis_utils.h"

int main (int argc, char **argv)
{
	t_node	*data;
	int		fd;
	size_t	sum1, sum2;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	data = populate_data(fd);

	// part 1
	sum1 = extrapolate_forwards(data);
	printf("part1 = %li\n", sum1);

	// part 2
	reverse_data(data);
	sum2 = extrapolate_forwards(data);
	printf("part2 = %li\n", sum2);

	// cleanup
	clear_nodes(&data);
	close(fd);
}

t_node	*populate_data(int fd)
{
	t_node	*data = NULL;
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		append_node(&data, new_node(parse_history(str)));
		free(str);
		str = get_next_line(fd);
	}
	return (data);
}

int	*parse_history(char *str)
{
	int	*history = calloc(SIZE, sizeof(int));
	int	i = 0;
	int	index = 0;
	
	while (str[i])
	{
		history[index] = atoi(str + i);
		while (isdigit(str[i]) || str[i] == '-')
			i++;
		while (isspace(str[i]))
			i++;
		index++;
	}
	return (history);
}

size_t	extrapolate_forwards(t_node *data)
{
	size_t	sum = 0;

	while (data)
	{
		sum += extrapolate_data(data->history, SIZE);
		data = data->next;
	}
	return (sum);
}

size_t	extrapolate_data(int *history, int size)
{
	size_t	sum = 0;
	int		check = 0;
	int		tmp;
	int		*diff_map = calloc(size - 1, sizeof(int));

	for (int i = 0; i < size - 1; i++)
		diff_map[i] = history[i + 1] - history[i];
	for (int j = 0; j < size - 1; j++)
	{
		if (diff_map[j] == 0)
			check++;
		if (check == size - 1)
		{
			tmp = history[j + 1] + diff_map[j];
			free(diff_map);
			return (tmp);
		}
	}
	if (size > 0)
		sum += extrapolate_data(diff_map, size - 1);
	sum = history[size - 1] + sum;
	free(diff_map);
	return (sum);
}
