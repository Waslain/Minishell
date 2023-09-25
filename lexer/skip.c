#include "minishell.h"

void	go_next_quote(char	*str, int *i, char quote)
{
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
}

void	skip_white_space(char *str, int *i)
{
	while (is_white_space(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
		(*i)++;
}

void	skip_token(char *str, int *i)
{
	while (!is_white_space(str[*i])
		&& !is_spec_char(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
			(*i)++;
}
