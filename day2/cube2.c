#include "get_next_line.h"
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int extract_game (char *str)
{
	int cube[3] = {0,0,0};
	int i = 0;
	int tmp = 0;
	int size = 0;
	int power = 0;
	
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
		printf("red %d green %d blue %d\n", cube[0], cube[1], cube[2]);
		if (str[i] == ';')
			i += 2;
		else
			break ;
	}
	power = cube[0] * cube[1] * cube[2];
	return (power);
}

int main (void)
{
	int fd;
	int nbr = 0;
	char *str;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("%s\n", str);
		nbr += extract_game(str);
		printf("nbr = %d\n", nbr);
		free(str);
	}
	free(str);
	printf("ID total %d\n", nbr);
}
