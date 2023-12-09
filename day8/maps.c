#include "aoc.h"
#include "maps.h"

int main (int argc, char **argv)
{
	t_node	*maps;
	t_node	*start;
	size_t	prime_factor;
	size_t	steps = 0;
	size_t	*steps2;
	char	*instructions;
	int		fd;
	int		points = 0;
	int		nbr = 2;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	instructions = get_next_line(fd);
	free(get_next_line(fd));

	// parse maps
	maps = populate_maps(fd);
	connect_maps(&maps);

	// find "ZZZ" exit with "AAA" as starting point
	start = start_position(maps, "AAA", 0);
	steps = find_path(&start, instructions, "ZZZ", 0);
	printf("part 1 %li\n", steps);

	// find all starting points ending in 'xxA'
	points = count_starting_points(maps);

	// finding all "xxZ" exits with "xxA" starts
	start = maps;
	steps2 = calloc(points, sizeof(size_t));
	for (int i = 0; i < points; i++)
	{
		start = start_position(start, "A", 2);
		steps2[i] = find_path(&start, instructions, "Z", 2);
		start = start->link;
	}

	// calculating LCM using division method
	while (steps2[0] % nbr != 0)
		nbr = find_next_prime(nbr);
	prime_factor = steps2[0] / nbr;
	for (int i = 0; i < points; i++)
	{
		nbr = 2;
		while (steps2[i] % nbr != 0)
			nbr = find_next_prime(nbr);
		prime_factor *= nbr;
	}
	printf("part 2 = %li\n", prime_factor);

	// cleanup
	free(steps2);
	free(instructions);
	clear_maps(&maps);
	close(fd);
}

t_node *populate_maps(int fd)
{
	t_node	*maps = NULL;
	char	*str = get_next_line(fd);
	
	while (str)
	{
		append_node(&maps, new_node(str));
		str = get_next_line(fd);
	}
	return (maps);
}

void	connect_maps(t_node **head)
{
	t_node	**tmp = head;
	t_node	*compare;
	int		size = maps_size(*head);

	for (int i = 0; i < size; i++)
	{
		compare = *head;
		for (int j = 0; j < size; j++)
		{
			if (!strncmp((*tmp)->current_map, compare->current_map + 7, 3))
				compare->left = *tmp;
			if (!strncmp((*tmp)->current_map, compare->current_map + 12, 3))
				compare->right = *tmp;
			compare = compare->link;
		}
		tmp = &(*tmp)->link;
	}
}

int	find_path(t_node **maps, char *instructions, const char *to_find, int offset)
{
	int	i;
	int	found = 0;
	int	steps = 0;
	int	len = 0;

	while (to_find[len])
		len++;
	while (found != 1)
	{
		i = 0;
		while (instructions[i] != '\n')
		{
			if (!strncmp((*maps)->current_map + offset, to_find, len))
			{
				found = 1;
				break ;
			}
			if (instructions[i] == 'L')
				maps = &(*maps)->left;
			else if (instructions[i] == 'R')
				maps = &(*maps)->right;
			steps++;
			i++;
		}
	}
	return (steps);
}

int	count_starting_points(t_node *maps)
{
	int	points = 0;

	while (maps)
	{
		if (!strncmp(maps->current_map + 2, "A", 1))
			points++;
		maps = maps->link;
	}
	return (points);
}

int	is_prime(int nbr)
{
	if (nbr <= 1)
		return (0);
	if (nbr <= 3)
		return (1);
	if (nbr % 2 == 0 || nbr % 3 == 0)
		return (0);
	for (int i = 5; i * i <= nbr; i = i + 6)
	{
		if (nbr % i == 0 || nbr % (i + 2) == 0)
			return (0);
	}
	return (1);
}

int	find_next_prime(int nbr)
{
	int prime = nbr;

	if (nbr <= 1)
		return (2);
	while (1)
	{
		prime++;
		if (is_prime(prime))
			break ;
	}
	return (prime);
}
