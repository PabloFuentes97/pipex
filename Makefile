SRCS =  main.c child.c pipex.c pipex_bonus.c ft_split.c get_next_line.c command_paths.c utils.c utils2.c
		
OBJS = ${SRCS:.c=.o}

CC = gcc -Wall -Werror -Wextra
LDFLAGS	= -fsanitize=address
CFLAGS = -Wextra -Wall -Werror #-fsanitize=address -g3

NAME = pipex

.c.o:
	${CC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
#		ar rc ${NAME} ${OBJS}
	$(CC) ${CFLAGS} -o $@ $^

all:		${NAME}

clean:
		rm -f ${OBJS} ${OBJSB}

fclean:		clean
		rm -f ${NAME}

re:		fclean all

bonus:		${NAME_B}

.PHONY: all clean fclean re bonus
