CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
EXEC	= minishell

INCLUDES		= ./includes/

SRCS = ./main.c

OBJS = ${SRCS:.c=.o}


all : $(EXEC)


$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -pthread $^ -o $(EXEC) -I $(INCLUDES) -g

.c.o:
	$(CC) $(CFLAGS) -pthread -c $^ -o $@ -I $(INCLUDES) -g

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC)

re : fclean all

.PHONY : all clean fclean re 