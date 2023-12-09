#include "aoc.h"

int main (int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc != 2)
		return (printf("Usage: %s <filename>\n", argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	
	str = get_next_line(fd);
	while (str)
	{
		/* code */
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
}
