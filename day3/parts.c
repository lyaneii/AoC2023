#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int issymbol(int c)
{
	if ((c >= '!' && c <= '-') || c == '/' || c == '@'
		|| (c >= ':' && c <= '?') || (c >= '{' && c <= '~'))
		return (1);
	return (0);
}

int convert_nbr(char *str, int i)
{
	int tmp = 0;
	int offset = 0;

	tmp = abs(atoi(str + i));
	offset = floor(log10(tmp)) + 1;
	while (str[i] && offset-- > 0)
		str[i + offset] = '.';
	return (tmp);
}

int check(char **str, int j)
{
	while (str[1][j] != '.' && str[1][j] != 0)
	{
		if (j != 0 && (issymbol(str[0][j - 1]) || issymbol(str[1][j - 1]) || issymbol(str[2][j - 1])))
			return (1);
		if (issymbol(str[0][j]) || issymbol(str[2][j]))
			return (1);
		if (issymbol(str[0][j + 1]) || issymbol(str[1][j + 1]) || issymbol(str[2][j + 1]))
			return (1);
		j++;
	}
	return (0);
}

char *empty(size_t size)
{
	size_t i = 0;
	char *empty = calloc(size + 1, sizeof(char));

	while (i < size - 1)
	{
		empty[i] = '.';
		i++;
	}
	empty[i] = '\n';
	return (empty);
}

int main(void)
{
	int fd = open("input.txt", O_RDONLY);
	int i = 0;
	int total = 0;
	int offset = 0;
	int len = 0;
	char **str;

	if (fd == -1)
		return (-1);
	str = calloc(4, sizeof(char *));
	str[1] = get_next_line(fd);
	str[2] = get_next_line(fd);
	len = strlen(str[1]);
	str[0] = empty(len);
	while (1)
	{
		if (!str[1])
			break ;
		
		while (str[1][i])
		{
			if (isdigit(str[1][i]) && check(str, i))
			{
				total += convert_nbr(str[1], i);
				printf("total %d\n", total);
			}
			i++;
		}
		i = 0;
		if (str[0])
			free(str[0]);
		str[0] = str[1];
		str[1] = str[2];
		str[2] = get_next_line(fd);
		if (!str[2])
			str[2] = empty(len);
	}
	close(fd);
}
