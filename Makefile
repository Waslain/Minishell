NAME		= minishell

# Path
INCS_PATH	= ./incs/
SRCS_PATH	= ./srcs/
OBJS_PATH	= ./objs/

# Files
DEBUG		= debug.c
LEXER		= lexer/check_char.c lexer/check_lexer.c lexer/count_token.c lexer/skip.c \
			lexer/spliters.c lexer/is_delimiter.c lexer/lexer.c lexer/lexer_expand.c \
			lexer/lexer_expand_utils.c lexer/lexer_utils.c lexer/check_lexer_utils.c \
			lexer/lexer_expand_utils2.c
PARSER		= parser/main.c parser/init_lex.c parser/init_cmds.c parser/init_redir.c parser/init_redir_utils.c
BUILTINS	= exec/builtin/builtin.c exec/builtin/echo.c exec/builtin/env.c exec/builtin/pwd.c exec/builtin/export.c \
			exec/builtin/unset.c exec/builtin/cd.c exec/builtin/exit.c
EXEC		= exec/main.c exec/parent.c exec/child.c exec/child_bis.c exec/open.c exec/close.c exec/execve.c \
			exec/convert_envp.c exec/envp_utils.c exec/error.c $(BUILTINS) $(HEREDOC)
HEREDOC		= exec/heredoc.c exec/heredoc_bis.c
UTILS		= utils/split.c utils/utils_1.c utils/utils_2.c utils/utils_3.c utils/utils_4.c utils/utils_5.c utils/utils_6.c
SRCS		= main.c minishell.c signals.c destroy_data.c $(LEXER) $(PARSER) $(EXEC) $(UTILS) $(DEBUG)
SRCS		:= $(addprefix $(SRCS_PATH), $(SRCS))
OBJS		:= $(subst $(SRCS_PATH), $(OBJS_PATH), $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

# Compilator
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS		+= -MMD -g3 -I $(INCS_PATH)
# CFLAGS		+= -O3
CFLAGS		+= -fsanitize=leak -fsanitize=undefined -fsanitize=address
LIBS		= -lreadline

# Rules
all		: $(NAME)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "Executable created"

leak	: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=./.readline.supp --track-origins=yes ./$(NAME)

clean	:
	@rm -rf $(OBJS_PATH) $(OBJS) $(DEPS)
	@echo "Objects deleted"

fclean	: clean
	@rm -rf $(NAME)
	@echo "Executable deleted"

re		: fclean all

# Rules for .o files
$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re

-include $(DEPS)