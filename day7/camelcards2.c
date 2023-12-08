#include "aoc.h"
#include "camelcards_utils.h"

int main (int argc, char **argv)
{
	t_hand *all_hands;
	size_t	total = 0;
	int		rank = 1;
	int 	fd;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	all_hands = sort_types(fd);
	sort_hands(&all_hands);
	while (all_hands)
	{
		printf("current hand | type %d | %s\n", all_hands->type, all_hands->hand);
		total += rank * current_bid(all_hands->hand);
		printf("rank %d total %li\n", rank, total);
		rank++;
		all_hands = all_hands->next;
	}
	printf("total = %ld\n", total);
	clear_hands(&all_hands);
	close(fd);
}

t_hand	*sort_types(int fd)
{
	t_hand *all_hands = NULL;
	Type type;
	char *str;
	
	str = get_next_line(fd);
	while (str)
	{
		type = hand_type(str);
		insert_hand(&all_hands, new_hand(str, type));
		str = get_next_line(fd);
	}
	return (all_hands);
}

Type	hand_type(char *str)
{
	char ignore_card = 0;
	Type type = check_type(str, &ignore_card);
	
	if (type == ONEPAIR || type == THREEKIND)
		return (type = fh_or_tp(str, type, &ignore_card));
	return (type);
}

Type	check_type(char *str, char *ignore_card)
{
	int i = 0;
	int cmp = 0;
	int pair = 0;

	while (i < 5)
	{
		while (str[i] == 'J')
			i++;
		cmp = i + 1;
		while (cmp < 5)
		{
			if (str[i] == str[cmp] && str[i] != 'J')
				pair++;
			cmp++;
		}
		if (pair != 0)
			break ;
		i++;
	}
	for (int j = 0; j < 5; j++)
	{
		if (str[j] == 'J')
			pair++;
	}
	switch (pair) {
		case 0:
			return (HIGHCARD);
		case 1:
			*ignore_card = str[i];
			return (ONEPAIR);
		case 2:
			*ignore_card = str[i];
			return (THREEKIND);
		case 3:
			return (FOURKIND);
		case 4:
			return (FIVEKIND);
		case 5:
			return (FIVEKIND);
	}
	return (0);
}

Type	fh_or_tp(char *str, Type type, char *ignore_card)
{
	int i = 0;
	int cmp = 0;
	int pair = 0;

	while (i < 5)
	{
		while (str[i] == *ignore_card && str[i] != 'J')
			i++;
		cmp = i + 1;
		while (cmp < 5)
		{
			if (str[i] == str[cmp] && str[i] != 'J')
				pair++;
			cmp++;
		}
		if (pair != 0)
			break ;
		i++;
	}
	if (pair == 1 && type == ONEPAIR)
		return (TWOPAIR);
	if ((pair == 1 && type == THREEKIND) || pair == 2)
		return (FULLHOUSE);
	return (type);
}

void	insert_hand(t_hand **all_hands, t_hand *new_hand)
{
	t_hand *insert;

	if (!*all_hands)
		*all_hands = new_hand;
	else if ((*all_hands)->type > new_hand->type)
	{
		new_hand->next = *all_hands;
		*all_hands = new_hand;
	}
	else
	{
		insert = insert_position(*all_hands, new_hand);
		new_hand->next = insert->next;
		insert->next = new_hand;
	}
}

void	sort_hands(t_hand **all_hands)
{
	t_hand **start;
	int swap = 1;
	int i, j;
	int size = sort_size(*all_hands);

	if (!*all_hands)
		return ;
	for (i = 0; i < size; i++)
	{
		start = all_hands;
		swap = 0;
		for (j = i; j < size - 1; j++)
		{
			if ((*start)->type == (*start)->next->type && is_stronger_hand(*start, (*start)->next))
			{
				*start = swap_hand(*start, (*start)->next);
				swap = 1;
			}
			convert_back2((*start)->hand);
			convert_back2((*start)->next->hand);
			start = &(*start)->next;
		}
		if (swap == 0)
			break ;
	}
}

int	is_stronger_hand(t_hand *current_hand, t_hand *next_hand)
{
	int i = 0;

	convert_symbols2(current_hand->hand);
	convert_symbols2(next_hand->hand);
	while (i < 5 && current_hand->hand[i] == next_hand->hand[i])
		i++;
	if (current_hand->hand[i] > next_hand->hand[i])
		return (1);
	return (0);
}
