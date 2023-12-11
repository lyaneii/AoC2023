#ifndef PIPE_UTILS_H
# define PIPE_UTILS_H
# include <stdlib.h>

// node helpers
typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;

t_node	*new_node(char *str);
t_node	*last_node(t_node *head);
void	append_node(t_node **head, t_node *new_node);
void	clear_nodes(t_node **head);

// map parsing
char	**parse_map(int fd);
char	*strddup(char *str, char delimiter);
int		find_start(char **map, char c);
int		row_contains_start(char *row, char c);
char	*empty_row(size_t len);

// map inversion
char	**duplicate_map(char **map);
void	fill_non_loop_areas(char **filled_map, char **inv_map, char fill);
void	invert_row(char *filled_row, char *inv_row, char fill);
void	close_loop_char(char **map, int row, char fill);

// navigation helpers
typedef enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	START,
	INVALID,
}	Nav;

Nav		evaluate_from_start(char **map, int row, int pos);
Nav		evaluate_north(char current_pos);
Nav		evaluate_east(char current_pos);
Nav		evaluate_south(char current_pos);
Nav		evaluate_west(char current_pos);
char	determine_loop_connection(char **map, int row, int pos);

// pathfinding
int		traverse_loop(char **map, int start_row, char fill);
Nav		determine_direction(char **map, int row, int column, Nav previous);
void	take_step(char **map, int *row, int *column, Nav direction, char fill);

// checking for enclosed area
int		evaluate_enclosed_areas(char **map, char fill);
int		evaluate_row(char *row, char fill);
int		evaluate_pipes(char *row, int *column);

#endif