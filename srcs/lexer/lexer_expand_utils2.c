/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:06:03 by fduzant           #+#    #+#             */
/*   Updated: 2023/11/01 12:12:56 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_next_simplequote(char *lex, int *i)
{
	(*i)++;
	go_next_quote(lex, i, '\'');
	(*i)++;
}

void	go_next_doublequote(char *lex, int *i)
{
	(*i)++;
	go_next_quote(lex, i, '"');
	(*i)++;
}

int	check_if_is_inside_dblquote(char *lex, int i)
{
	int	nb_quote;
	int	x;

	nb_quote = 0;
	x = 0;
	while (x < i)
	{
		if (lex[x] == '"')
			nb_quote++;
		x++;
	}
	if (nb_quote % 2 == 0)
		return (0);
	else
		return (1);
}

int	check_nextquote(char *lex)
{
	int	nb_quote;
	int	i;

	nb_quote = 0;
	i = 0;
	while (lex[i] != '\0')
	{
		if (lex[i] == '\'')
			nb_quote++;
		i++;
	}
	if (nb_quote > 0)
		return (0);
	else
		return (1);
}
