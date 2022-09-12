NAME	=	pipex

SRCS			=	pipex.c 	\
					error.c 	\
					utils.c


OBJS			=	${SRCS:.c=.o}

LIB_FLAGS		=	-L libft

HFLAGS			=	-I. -I libft

CC				=	gcc -g

CFLAGS			=	-Wall -Werror -Wextra

.c.o			:
					${CC} ${CFLAGS} ${HFLAGS} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C libft
					${CC} ${CFLAGS} ${LIB_FLAGS} ${OBJS} -o ${NAME} -lft

all				:	${NAME}

clean			:
					make clean -C libft
					rm -rf ${OBJS}

fclean			:	clean
					make fclean -C libft
					rm -rf ${NAME}

re				:	fclean all