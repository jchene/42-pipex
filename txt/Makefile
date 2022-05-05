NAME		=	pipex

HEADER		=	./pipex.h

SRCS		=	./srcs/lib.c\
				./srcs/print.c\
				./srcs/exit.c\
				./srcs/memory.c\
				./srcs/parsing.c\

MAIN		=	./srcs/main.c\

TEST_MAIN	=	./srcs/test.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

LSANF		=	-fsanitize=address

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(MAIN) $(CFLAGS)

test:			$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(TEST_MAIN) $(CFLAGS) -g $(LSANF)

leak:			$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g $(LSANF)

g:				$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g

force:			$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(MAIN)

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all test leak g force clean fclean re
