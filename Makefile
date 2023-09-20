CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
EXEC	= minishell

INCLUDES		= ./includes/

SRCS = ./main.c ./utils.c ./ft_split.c ./exec.c ./libft.c ./newpipe.c

OBJS = ${SRCS:.c=.o}


all : $(EXEC)


$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -g3 $^ -o $(EXEC) -I $(INCLUDES) -g -lreadline

.c.o:
	$(CC) $(CFLAGS) -g3 -c $^ -o $@ -I $(INCLUDES) -g

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC)

re : fclean all

.PHONY : all clean fclean re 