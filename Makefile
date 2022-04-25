NAME		=	pipex

HEADER		=	./pipex.h

SRCS		=	./srcs/main.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

LSANF		=	-fsanitize=address

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS)

leaksan:		$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g $(LSANF)

g:				$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all leaksan g clean fclean re
