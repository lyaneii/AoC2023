#ifndef AOC_H
# define AOC_H
# include "../codam_gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <math.h>
# include <string.h>

void	free_all(void **ptr, int size)
{
	int i = 0;

	while (i < size)
		free(ptr[i]);
	free(ptr);
	ptr = NULL;
}

void	print_long_array(long *arr, const char *str, int size)
{
	int i = 0;

	printf("%s ", str);
	printf("{");
	while (i < size)
	{
		printf("%li", arr[i]);
		i++;
		if (i < size)
			printf(",");
	}
	printf("}\n");
}

void	print_int_array(int *arr, const char *str, int size)
{
	int i = 0;

	printf("%s ", str);
	printf("{");
	while (i < size)
	{
		printf("%d", arr[i]);
		i++;
		if (i < size)
			printf(",");
	}
	printf("}\n");
}

#endif