/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:06:03 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/28 00:37:20 by obouhlel         ###   ########.fr       */
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
