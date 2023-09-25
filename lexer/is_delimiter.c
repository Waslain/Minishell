#include "minishell.h"

int	is_delimiter(char *lex)
{
	if (ft_strcmp(lex, "<") == 0)
		return (1);
	else if (ft_strcmp(lex, ">") == 0)
		return (1);
	else if (ft_strcmp(lex, "<<") == 0)
		return (1);
	else if (ft_strcmp(lex, ">>") == 0)
		return (1);
	else
		return (0);
}
