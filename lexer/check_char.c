#include "minishell.h"

int	is_white_space(char c)
{
	return (c == ' '
		|| (c >= 9 && c <= 13)
		|| c == '\n');
}

int	is_spec_char(char c)
{
	return ((c == '|')
		|| (c == '<')
		|| (c == '>'));
}

int	is_quote(char c)
{
	return ((c == '\'')
		|| (c == '"'));
}
