#include "../codam_gnl/get_next_line.h"
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

static void	strrev(char *str, int size)
{
	int i = 0;
	char tmp;

	while (i < size / 2)
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
		i++;
	}
}

static int nbr_rcmp(char *str)
{
	if (!strncmp("eno", str, 3))
		return (1);
	else if (!strncmp("owt", str, 3))
		return (2);
	else if (!strncmp("eerht", str, 5))
		return (3);
	else if (!strncmp("ruof", str, 4))
		return (4);
	else if (!strncmp("evif", str, 4))
		return (5);
	else if (!strncmp("xis", str, 3))
		return (6);
	else if (!strncmp("neves", str, 5))
		return (7);
	else if (!strncmp("thgie", str, 5))
		return (8);
	else if (!strncmp("enin", str, 4))
		return (9);
	return (0);
}

static int nbr_cmp(char *str)
{
	if (!strncmp("one", str, 3))
		return (1);
	else if (!strncmp("two", str, 3))
		return (2);
	else if (!strncmp("three", str, 5))
		return (3);
	else if (!strncmp("four", str, 4))
		return (4);
	else if (!strncmp("five", str, 4))
		return (5);
	else if (!strncmp("six", str, 3))
		return (6);
	else if (!strncmp("seven", str, 5))
		return (7);
	else if (!strncmp("eight", str, 5))
		return (8);
	else if (!strncmp("nine", str, 4))
		return (9);
	return (0);
}

int main (void)
{
	int fd;
	char *str;
	int i = 0;
	int j = 0;
	int nbr = 0;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		i = 0;
		j = strlen(str);
		while (str[i])
		{
			if (isdigit(str[i]))
			{
				nbr += (str[i] - '0') * 10;
				break ;
			}
			else if (nbr_cmp(str + i) != 0)
			{
				nbr += nbr_cmp(str + i) * 10;
				break ;
			}
			i++;
		}
		strrev(str, j - 1);
		i = 0;
		while (str[i])
		{
			if (isdigit(str[i]))
			{
				nbr += (str[i] - '0');
				break ;
			}
			else if (nbr_rcmp(str + i) != 0)
			{
				nbr += nbr_rcmp(str + i);
				break ;
			}
			i++;
		}
		free(str);
	}
	close(fd);
	printf("nbr = %d\n", nbr);
	return (0);
}
