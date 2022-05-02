NAME		=	pipex

HEADER		=	./pipex.h

SRCS		=	./srcs/test.c\
				./srcs/lib.c\
				./srcs/print.c\
				./srcs/exit.c\
				./srcs/memory.c\

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

leak:			$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g $(LSANF)

g:				$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all leak g clean fclean re
