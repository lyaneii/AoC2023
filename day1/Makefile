NAME = output

SRC = calib.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	cc -o ${NAME} ${OBJ} -L../codam_gnl -lgnl

%.o: %.c
	cc -I../codam_gnl -c $< -o $@
clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re