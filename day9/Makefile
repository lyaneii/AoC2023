NAME = output

SRC = oasis.c oasis_utils.c

CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${MAKE} -C ../codam_gnl
	cc ${CFLAGS} -g -o ${NAME} ${OBJ} -L../codam_gnl -lgnl -L/usr/lib -lm

%.o: %.c
	cc ${CFLAGS} -g -I../codam_gnl -I../include -c $< -o $@
clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re