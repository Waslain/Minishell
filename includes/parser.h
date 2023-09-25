#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# define FILES_IN 0
# define FILES_OUT 1
# define HEREDOC 2
# define PIPE 3
# define CMD 4
# define ARGS 5
# define SIMPLE_QUOTE 6
# define DOUBLE_QUOTE 7
# define REDIR_IN 8
# define REDIR_OUT 9
# define APPEND_IN 10
# define APPEND_OUT 11

/* STRUCTURE */
typedef struct s_bloc
{
	char			*content;
	struct	s_bloc	*next;
	int				type;
}	t_bloc;

typedef struct s_lexer
{
	char	*text;
	int		pos;
	char	current_char;
}	t_lexer;

#endif