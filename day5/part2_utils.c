#include "part2_utils.h"
#include <stdlib.h>
#include <stdio.h>

t_seedrange *last_seed(t_seedrange *seed_ranges)
{
	if (!seed_ranges)
		return (NULL);
	while (seed_ranges->next)
		seed_ranges = seed_ranges->next;
	return (seed_ranges);
}

t_seedrange *new_seed_range(long start, long range)
{
	t_seedrange *new_seed_range;

	new_seed_range = malloc(sizeof(t_seedrange));
	if (!new_seed_range)
		return (NULL);
	
	new_seed_range->start = start;
	new_seed_range->range = range;
	new_seed_range->next = NULL;

	return (new_seed_range);
}

void	append_seedrange(t_seedrange **seed_ranges, t_seedrange *new_seed_range)
{
	if (!*seed_ranges)
		*seed_ranges = new_seed_range;
	else
		last_seed(*seed_ranges)->next = new_seed_range;
}

void	clear_seedrange(t_seedrange **seed_ranges)
{
	t_seedrange *tmp;

	while (*seed_ranges)
	{
		tmp = *seed_ranges;
		*seed_ranges = (*seed_ranges)->next;
		free(tmp);
	}
	*seed_ranges = NULL;
}

void	inside_bounds(t_seedrange **tmp, long start, long range)
{
	append_seedrange(tmp, new_seed_range(start, range));
}

void	outside_bounds(t_seedrange **tmp, long start, long range)
{
	append_seedrange(tmp, new_seed_range(start, range));
}
