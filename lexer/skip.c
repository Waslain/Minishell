/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
