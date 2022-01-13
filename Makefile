SRCS_S =	serveur.c
SRCS_C =	client.c \
			minitalk_utils.c
OBJS_C =	${SRCS_C:.c=.o}
OBJS_S =	${SRCS_S:.c=.o}
HEADERS =	minitalk.h
NAME_C =	client
NAME_S =	serveur
NAME =
RM =		rm -f
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
LIBFT =		libft/libft.a

%.o:		%.c ${HEADERS}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		libft ${NAME_C} ${NAME_S}

${NAME}:	all

${NAME_S}:	${LIBFT} ${OBJS_S} minitalk_utils.o
			${CC} ${CFLAGS} ${OBJS_S} minitalk_utils.o ./libft/libft.a -o ${NAME_S}

${NAME_C}:	${LIBFT} ${OBJS_C}
			${CC} ${CFLAGS} ${OBJS_C} ./libft/libft.a -o ${NAME_C}

libft:		
			$(MAKE) -C ./libft

bonus: all

clean:	
			$(MAKE) clean -C ./libft
			${RM} ${OBJS_C} ${OBJS_S}

fclean:		clean
			${RM} ${NAME_S} ${NAME_C}
			$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all bonus clean fclean libft