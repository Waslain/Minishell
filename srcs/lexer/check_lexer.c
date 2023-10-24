/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 17:51:15 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (ft_strcmp(lex[i], "|") == 0)
		{
			if (i == 0 || lex[i + 1] == NULL)
				return (print_delimiter_error(lex[i]), 0);
			if (ft_strcmp(lex[i + 1], "|") == 0)
				return (print_delimiter_error(lex[i]), 0);
		}
		i++;
	}
	return (1);
}

int	check_quote(char *lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (lex[i] == '"')
		{
			i++;
			go_next_quote(lex, &i, '"');
			if (lex[i] != '"')
				return (print_delimiter_error(lex), 0);
		}
		else if (lex[i] == '\'')
		{
			i++;
			go_next_quote(lex, &i, '\'');
			if (lex[i] != '\'')
				return (print_delimiter_error(lex), 0);
		}
		i++;
	}
	return (1);
}

static int	check_delimiters(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (is_delimiter(lex[i]))
		{
			if (lex[i + 1] == NULL
				|| is_delimiter(lex[i + 1])
				|| ft_strcmp(lex[i + 1], "|") == 0)
			{
				print_delimiter_error(lex[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_lexer(char **lex)
{
	if (!check_pipe(lex))
		return (0);
	if (!check_delimiters(lex))
		return (0);
	return (1);
}
