NAME = output

SRC = seed2.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${MAKE} -C ../codam_gnl
	cc -o ${NAME} ${OBJ} -L../codam_gnl -lgnl -L/usr/lib -lm

%.o: %.c
	cc -I../codam_gnl -I../include -c $< -o $@
clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re