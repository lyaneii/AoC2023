#ifndef PART2_UTILS_H
# define PART2_UTILS_H

typedef struct s_seedrange
{
	long start;
	long range;
	struct s_seedrange *next;

}	t_seedrange;

t_seedrange *last_seed(t_seedrange *seed_ranges);
t_seedrange *new_seed_range(long start, long range);
void		append_seedrange(t_seedrange **seed_ranges, t_seedrange *new_seed_range);
void		clear_seedrange(t_seedrange **seed_ranges);
void		inside_bounds(t_seedrange **tmp, long start, long range);
void		outside_bounds(t_seedrange **tmp, long start, long range);

#endif
