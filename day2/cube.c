#include "get_next_line.h"
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define RED 12
#define GREEN 13
#define BLUE 14

int valid_check(int *cube)
{
	if (cube[0] > RED || cube[1] > GREEN || cube[2] > BLUE)
		return (0);
	return (1);
}

int extract_game (char *str)
{
	int cube[3] = {0,0,0};
	int i = 0;
	int tmp = 0;
	int size = 0;
	
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
					cube[0] = tmp;
					i += 3;
					break ;
				case 'g':
					cube[1] = tmp;
					i += 5;
					break ;
				case 'b':
					cube[2] = tmp;
					i += 4;
					break ;
			}
			if (str[i] == ',')
				i += 2;
			else
				break ;
		}
		printf("red %d green %d blue %d\n", cube[0], cube[1], cube[2]);
		if (!valid_check(cube))
			return (0);
		cube[0] = 0;
		cube[1] = 0;
		cube[2] = 0;
		if (str[i] == ';')
			i += 2;
		else
			break ;
	}
	return (1);
}

int main (void)
{
	int fd;
	int nbr = 0;
	int count = 1;
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
		if (extract_game(str))
			nbr += count;
		printf("nbr = %d\n", nbr);
		count++;
		free(str);
	}
	free(str);
	printf("ID total %d\n", nbr);
}
