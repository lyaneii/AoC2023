#ifndef CAMELCARDS_UTILS_H
# define CAMELCARDS_UTILS_H

typedef enum Handtype
{
	HIGHCARD,
	ONEPAIR,
	TWOPAIR,
	THREEKIND,
	FULLHOUSE,
	FOURKIND,
	FIVEKIND
}	Type;

typedef struct s_hand
{
	char			*hand;
	Type			type;
	struct s_hand	*next;
}	t_hand;

Type	hand_type(char *str);
Type	check_type(char *str, char *ignore_card);
Type	fh_or_tp(char *str, Type type, char *ignore_card);
t_hand	*sort_types(int fd);
t_hand	*insert_position(t_hand *all_hands, t_hand *new_hand);
void	insert_hand(t_hand **all_hands, t_hand *new_hand);
t_hand	*new_hand(char *str, Type type);
void	clear_hands(t_hand **all_hands);
void	sort_hands(t_hand **all_hands);
int		sort_size(t_hand *all_hands);
int		is_stronger_hand(t_hand *current_hand, t_hand *next_hand);
void	convert_symbols(char *hand);
void	convert_back(char *hand);
void	convert_symbols2(char *hand);
void	convert_back2(char *hand);
t_hand	*swap_hand(t_hand *current_hand, t_hand *next_hand);
int		current_bid(char *current_hand);

#endif