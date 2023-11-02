/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:06:03 by fduzant           #+#    #+#             */
/*   Updated: 2023/11/02 21:49:37 by fduzant          ###   ########.fr       */
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

void	set_inquote_to_false(int *i, bool *inquote)
{
	*inquote = false;
	(*i)++;
}

void	set_inquote_to_true(int *i, bool *inquote)
{
	*inquote = true;
	(*i)++;
}

char	*if_not_dollars_exec(char *new_lex, char *lex, int i, int x)
{
	char	*tmp;

	tmp = new_lex;
	new_lex = ft_strjoinn(new_lex, &lex[i], x - 1);
	if (!new_lex)
		return (free(tmp), NULL);
	free(tmp);
	return (new_lex);
}
