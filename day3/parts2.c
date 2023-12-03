#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int issymbol(int c)
{
	if (c == '*')
		return (1);
	return (0);
}

int convert_nbr(char *str, int i)
{
	int tmp = 0;
	int offset = 0;

	while (!isdigit(str[i]))
		i--;
	while (isdigit(str[i - 1]) && i > 0)
		i--;
	// printf("%c %s\n", str[i], str);
	tmp = abs(atoi(str + i));
	// printf("nbr %d\n", tmp);
	offset = floor(log10(tmp)) + 1;
	while (str[i] && offset-- > 0)
		str[i + offset] = '.';
	// printf("nbr %d\n", tmp);
	return (tmp);
}

int check(char **str, int j)
{
	while (str[1][j] != '.' && str[1][j] != 0)
	{
		if (j == 0)
			j++;
		if (isdigit(str[0][j - 1]) || isdigit(str[0][j]) || isdigit(str[0][j + 1]))
			return (1);
		if (isdigit(str[1][j - 1]) || isdigit(str[1][j + 1]))
			return (2);
		if (isdigit(str[2][j - 1]) || isdigit(str[2][j]) || isdigit(str[2][j + 1]))
			return (3);
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

int main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	int i = 0;
	int total = 0;
	int offset = 0;
	int len = 0;
	int tmp1 = 0;
	int tmp2 = 0;
	int tmp_i = 0;
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
			tmp1 = 0;
			tmp2 = 0;
			if (issymbol(str[1][i]))
			{
				// printf("map \n%s%s%s\n", str[0], str[1], str[2]);
				switch (check(str, i))
				{
					case 0:
						break ;
					case 1:
						tmp1 = convert_nbr(str[0], i + 1);
						break ;
					case 2:
						tmp1 = convert_nbr(str[1], i + 1);
						break ;
					case 3:
						tmp1 = convert_nbr(str[2], i + 1);
						break ;
				}
				// printf("%d\n", tmp1);
				if (tmp1 != 0)
				{
					switch (check(str, i))
					{
						case 0:
							break ;
						case 1:
							tmp2 = convert_nbr(str[0], i + 1);
							break ;
						case 2:
							tmp2 = convert_nbr(str[1], i + 1);
							break ;
						case 3:
							tmp2 = convert_nbr(str[2], i + 1);
							break ;
					}
				}
				// printf("%d\n", tmp2);
				if (tmp2 != 0)
					total += tmp1 * tmp2;
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
	}
	close(fd);
}
