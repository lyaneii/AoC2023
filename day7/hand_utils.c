#include "camelcards_utils.h"
#include <stdlib.h>

t_hand	*new_hand(char *str, Type type)
{
	t_hand	*new_hand;

	new_hand = malloc(sizeof(t_hand));
	if (!new_hand)
		return (NULL);
	new_hand->hand = str;
	new_hand->type = type;
	new_hand->next = NULL;

	return (new_hand);
}

void	clear_hands(t_hand **all_hands)
{
	t_hand *tmp;

	while (*all_hands)
	{
		tmp = *all_hands;
		*all_hands = (*all_hands)->next;
		free(tmp->hand);
		free(tmp);
	}
	*all_hands = NULL;
}

int	current_bid(char *current_hand)
{
	return (atoi(current_hand + 6));
}

t_hand	*swap_hand(t_hand *current_hand, t_hand *next_hand)
{
	t_hand	*tmp;
	
	tmp = next_hand->next;
	next_hand->next = current_hand;
	current_hand->next = tmp;
	return (next_hand);
}

void	convert_symbols(char *hand)
{
	for (int i = 0; i < 5; i++)
	{
		if (hand[i] == 'J')
			hand[i] = 'U';
		else if (hand[i] == 'Q')
			hand[i] = 'V';
		else if (hand[i] == 'K')
			hand[i] = 'W';
		else if (hand[i] == 'A')
			hand[i] = 'X';	
	}
}

void	convert_back(char *hand)
{
	for (int i = 0; i < 5; i++)
	{
		if (hand[i] == 'U')
			hand[i] = 'J';
		else if (hand[i] == 'V')
			hand[i] = 'Q';
		else if (hand[i] == 'W')
			hand[i] = 'K';
		else if (hand[i] == 'X')
			hand[i] = 'A';	
	}
}

void	convert_symbols2(char *hand)
{
	for (int i = 0; i < 5; i++)
	{
		if (hand[i] == 'J')
			hand[i] = '1';
		else if (hand[i] == 'Q')
			hand[i] = 'V';
		else if (hand[i] == 'K')
			hand[i] = 'W';
		else if (hand[i] == 'A')
			hand[i] = 'X';	
	}
}

void	convert_back2(char *hand)
{
	for (int i = 0; i < 5; i++)
	{
		if (hand[i] == '1')
			hand[i] = 'J';
		else if (hand[i] == 'V')
			hand[i] = 'Q';
		else if (hand[i] == 'W')
			hand[i] = 'K';
		else if (hand[i] == 'X')
			hand[i] = 'A';	
	}
}

t_hand	*insert_position(t_hand *all_hands, t_hand *new_hand)
{
	while (all_hands->next && all_hands->next->type < new_hand->type)
		all_hands = all_hands->next;
	return (all_hands);
}

int	sort_size(t_hand *all_hands)
{
	int size = 0;

	while (all_hands)
	{
		size++;
		all_hands = all_hands->next;
	}
	return (size);
}
