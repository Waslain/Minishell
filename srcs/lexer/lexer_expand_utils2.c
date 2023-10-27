/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:06:03 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/27 13:11:32 by fduzant          ###   ########.fr       */
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
