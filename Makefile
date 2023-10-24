NAME		= minishell

# Path
INCS_PATH	= ./incs/
SRCS_PATH	= ./srcs/
OBJS_PATH	= ./objs/

# Files
LEXER		= lexer/check_char.c lexer/check_lexer.c lexer/count_token.c lexer/skip.c \
			lexer/spliters.c lexer/is_delimiter.c lexer/lexer.c lexer/lexer_expand.c \
			lexer/lexer_expand_utils.c lexer/lexer_utils.c
PARSER		= parser/parser.c parser/open_file.c parser/init_lex.c parser/init_cmd_tab.c
EXEC		= exec/exec_cmd.c exec/exec_error.c exec/exec_no_pipe.c exec/exec_pipe.c exec/builtin/builtin.c \
			exec/builtin/echo.c exec/builtin/pwd.c exec/builtin/env.c exec/builtin/exit.c
UTILS		= utils.c ft_split.c libft/libft.c libft/libft1.c
SRCS		= main.c exec.c signals.c $(LEXER) $(PARSER) $(EXEC) $(UTILS)
SRCS		:= $(addprefix $(SRCS_PATH), $(SRCS))
OBJS		:= $(subst $(SRCS_PATH), $(OBJS_PATH), $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

# Compilator
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -g3 -I $(INCS_PATH)
LIBS		= -lreadline

# Rules
all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "Executable created"

clean :
	@rm -rf $(OBJS_PATH) $(OBJS) $(DEPS)
	@echo "Objects deleted"

fclean : clean
	@rm -rf $(NAME)
	@echo "Executable deleted"

re : fclean all

# Rules for .o files
$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re