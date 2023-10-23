CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
EXEC	= minishell

INCLUDES		= ./includes/

SRCS = ./main.c ./utils.c ./ft_split.c ./exec.c ./signals.c \
		./lexer/check_char.c \
		./lexer/check_lexer.c \
		./lexer/count_token.c \
		./lexer/skip.c \
		./lexer/spliters.c \
		./lexer/is_delimiter.c \
		./lexer/lexer.c \
		./lexer/lexer_expand.c \
		./lexer/lexer_expand_utils.c \
		./lexer/lexer_utils.c \
		./exec/exec_cmd.c \
		./exec/exec_error.c \
		./exec/exec_no_pipe.c \
		./exec/exec_pipe.c \
		./exec/builtin/builtin.c \
		./exec/builtin/echo.c \
		./exec/builtin/pwd.c \
		./exec/builtin/env.c \
		./exec/builtin/exit.c \
		./parser/parser.c \
		./parser/open_file.c \
		./parser/init_lex.c \
		./parser/init_cmd_tab.c \
		./libft/libft.c \
		./libft/libft1.c \

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