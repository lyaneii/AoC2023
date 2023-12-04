#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define CARD_SIZE 10
#define OWN_SIZE 25
// input 10 25
// test 5 8

static void printarray(int *arr, const char *str, int size)
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

int nbcmp(int *card, int *own)
{
	int total = 0;
	int i = 0;
	int index = 0;

	// printarray(card, "card", CARD_SIZE);
	// printarray(own, "own", OWN_SIZE);
	while (card[i])
	{
		index = 0;
		while (own[index])
		{
			if (card[i] == own[index])
			{
				if (total != 0)
					total *= 2;
				else
					total = 1;
			}
			index++;
		}
		i++;
	}
	return (total);
}

int main (int argc, char **argv)
{
	int fd;
	int total = 0;
	int i = 0;
	int index = 0;
	int *card;
	int *own;
	char *str;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	while (1)
	{
		// initialise variables
		i = 0;
		index = 0;
		str = get_next_line(fd);
		if (!str)
			break ; 
		card = calloc(CARD_SIZE + 1, sizeof(int));
		if (!card)
			return (free(str), -1);
		own = calloc(OWN_SIZE + 1, sizeof(int));
		if (!own)
			return (free(str), free(card), -1);
		
		// skip to the first set of numbers
		while (str[i] != ':')
			i++;
		while (!isdigit(str[i]))
			i++;

		// populating the array containing the card's numbers
		while (str[i] != '|')
		{
			if (isdigit(str[i]))
			{
				card[index] = atoi(str + i);
				i += card[index] < 10 ? 1 : 2;
				index++;
			}
			i++;
		}

		// skip to the next set of numbers & reset the array index
		while (!isdigit(str[i]))
			i++;
		index = 0;

		// populating the array containing our own numbers
		while (str[i])
		{
			if (isdigit(str[i]))
			{
				own[index] = atoi(str + i);
				i += own[index] < 10 ? 1 : 2;
				index++;
			}
			i++;
		}

		// adding total numbers together
		total += nbcmp(card, own);
		printf("total: %d\n", total);

		// free old pointers
		free(card);
		free(own);
		free(str);
	}
	close (fd);
}
