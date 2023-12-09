#ifndef OASIS_UTILS_H
# define OASIS_UTILS_H
# include <stdlib.h>
# define SIZE 21

typedef struct s_node
{
	int	*history;
	struct s_node *next;
}	t_node;

t_node	*new_node(int *history);
t_node	*last_node(t_node *head);
void	append_node(t_node **head, t_node *new_node);
void	clear_nodes(t_node **head);
t_node	*populate_data(int fd);
int		*parse_history(char *str);
size_t	extrapolate_forwards(t_node *data);
size_t	extrapolate_data(int *history, int size);
void	reverse_data(t_node *data);
void	reverse_array(int *array, int size);

#endif