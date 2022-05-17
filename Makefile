NAME		=	pipex

HEADER		=	./pipex.h

SRCS		=	./srcs/lib.c\
				./srcs/print.c\
				./srcs/exit.c\
				./srcs/memory.c\
				./srcs/string.c\
				./srcs/path.c\
				./srcs/main.c\
				./srcs/init.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall -g

LSANF		=	-fsanitize=address

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

leak:			$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -g $(LSANF)

force:			$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(OBJ)

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all leak force clean fclean re
