#include "aoc.h"

int main (int argc, char **argv)
{
	int fd;
	int i = 0;
	char *str;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	while (1)
	{
		// initialise variables
		str = get_next_line(fd);
		if (!str)
			break ;
	}
	close(fd);
}
