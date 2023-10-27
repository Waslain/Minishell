/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:55:57 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 15:30:50 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_delimiter_error(char *delimiter)
{
	print_error("minishell: syntax error near unexpected token '");
	print_error(delimiter);
	print_error("'\n");
}

static bool	is_invalid_char(char c)
{
	const char	*invalid = INVALID_CHAR;
	int			i;

	i = 0;
	while (invalid[i])
	{
		if (invalid[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	chek_invalidchar(char *lex)
{
	int			i;

	i = 0;
	while (lex[i])
	{
		if (is_invalid_char(lex[i]))
		{
			return (print_delimiter_error(lex), 0);
		}
		if (lex[i] == '"')
		{
			i++;
			go_next_quote(lex, &i, '"');
		}
		else if (lex[i] == '\'')
		{
			i++;
			go_next_quote(lex, &i, '\'');
		}
		i++;
	}
	return (1);
}
