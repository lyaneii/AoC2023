#ifndef MAPS_H
# define MAPS_H
# include <stdlib.h>

typedef struct s_node
{
	char			*current_map;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*link;
}	t_node;

t_node *populate_maps(int fd);
void	connect_maps(t_node **head);
t_node *new_node(char *current_map);
t_node	*last_node(t_node *head);
t_node	*start_position(t_node *head, const char *to_find, int offset);
void	append_node(t_node **head, t_node *new_node);
void	clear_maps(t_node **head);
int		maps_size(t_node *head);
int		find_path(t_node **maps, char *instructions, const char *to_find, int offset);
int		count_starting_points(t_node *maps);
int 	is_prime(int nbr);
int 	find_next_prime(int nbr);
#endif