#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define RED 12
#define GREEN 13
#define BLUE 14

static int valid_check(int *cube)
{
	if (cube[0] > RED || cube[1] > GREEN || cube[2] > BLUE)
		return (0);
	return (1);
}

static int *extract_game (char *str)
{
	int cube[3] = {0,0,0};
	int i = 0;
	int tmp = 0;
	int size = 0;
	int *nbr;
	
	nbr = calloc(2, sizeof(int));
	if (!nbr)
		return (NULL);
	while (str[i] != ':')
		i++;
	i += 2;
	while (str[i])
	{
		while (str[i] != ';')
		{
			tmp = atoi(str + i);
			size = tmp < 10 ? 2 : 3;
			i += size;
			switch(str[i])
			{
				case 'r':
					cube[0] = cube[0] > tmp ? cube[0] : tmp;
					i += 3;
					break ;
				case 'g':
					cube[1] = cube[1] > tmp ? cube[1] : tmp;
					i += 5;
					break ;
				case 'b':
					cube[2] = cube[2] > tmp ? cube[2] : tmp;
					i += 4;
					break ;
			}
			if (str[i] == ',')
				i += 2;
			else
				break ;
		}
		if (str[i] == ';')
			i += 2;
		else
			break ;
	}
	if (valid_check(cube))
		nbr[0] = 1;
	nbr[1] = cube[0] * cube[1] * cube[2];
	return (nbr);
}

int main (void)
{
	int fd;
	int power = 0;
	int id = 0;
	int count = 1;
	int *nbr;
	char *str;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		nbr = extract_game(str);
		if (!nbr)
			return (free(str), -1);
		if (nbr[0] == 1)
			id += count;
		power += nbr[1];
		count++;
		free(nbr);
		free(str);
	}
	printf("id total %d, power total %d\n", id, power);
}
