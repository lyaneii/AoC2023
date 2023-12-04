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
				total++;
			index++;
		}
		i++;
	}
	return (total);
}

void	add_copies(int *track_copies, int size, int amount)
{
	int i = 0;

	while (i < size)
	{
		track_copies[i + 1] += 1 * amount;
		i++;
	}
}

void	shift_track(int *track_copies, int size)
{
	int i = 0;

	// printarray(track_copies, "before shift", size);
	while (i < size)
	{
		track_copies[i] = track_copies[i + 1];
		i++;
	}
	// printarray(track_copies, "after shift", size);
}

int main (int argc, char **argv)
{
	int fd;
	int total = 0;
	int counter = 0;
	int i = 0;
	int index = 0;
	int copies = 0;
	int *card;
	int *own;
	int *track_copies;
	char *str;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	// storing the copies
	track_copies = calloc(OWN_SIZE + 1, sizeof(int));
	if (!track_copies)
		return (close(fd));
	
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
			return (free(track_copies), free(str), -1);
		own = calloc(OWN_SIZE + 1, sizeof(int));
		if (!own)
			return (free(track_copies), free(str), free(card), -1);
		
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

		// counting amount of matching numbers which determine the amount of copies
		copies = nbcmp(card, own);

		// adding the amount of copies(copies) the current cards(track_copies[0] + 1) have made
		add_copies(track_copies, copies, track_copies[0] + 1);

		// adding up ONLY the copies to the total amount of cards
		total += ((track_copies[0] + 1) * copies);

		// shifting the track to the next set of cards
		shift_track(track_copies, OWN_SIZE);

		// keeping track of the original cards
		counter++;

		// free old pointers
		free(card);
		free(own);
		free(str);
	}
	// adding the original cards to the total amount
	total += counter;
	printf("final nbr: %d\n", total);

	// free pointers
	free(track_copies);
	close (fd);
}
