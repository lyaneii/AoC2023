#ifndef COSMIC_UTILS_H
# define COSMIC_UTILS_H
# include <stdlib.h>

// map helpers
typedef struct s_map
{
	char			*str;
	int				row;
	int				column;
	struct s_map	*next;
}	t_map;

t_map	*new_map(char *str, int row, int column);
t_map	*last_map(t_map *head);
void	append_map(t_map **head, t_map *new_map);
void	clear_map(t_map **head);

// map parsing
t_map	*parse_map(int fd, int **expand_rows, int **expand_columns);
char	**tmp_map(t_map *tmp, int size);
void	check_expansions(char **map, t_map **expansions);
int		row_has_galaxy(char *row);
int		column_has_galaxy(char **map, int row, int column);
int		*parse_row_expansions(t_map *expansions);
int		*parse_column_expansions(t_map *expansions);
int		expansion_amount(t_map *expansions, const char check);
t_map	*galaxy_coords(char **map);

// connecting galaxies
size_t	connect_galaxies(t_map *current, int *expand_rows, int *expand_columns, int size);
int		expansions_in_range(int start, int end, int *expansion, int size);

#endif