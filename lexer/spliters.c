/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_split_len_process(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		len++;
		while (str[i + len] != str[i])
			len++;
		len++;
	}
	else
	{
		while (str[i + len] != '\0'
			&& !is_white_space(str[i + len])
			&& str[i + len] != '\''
			&& str[i + len] != '"'
			&& !is_spec_char(str[i + len]))
			len++;
	}
	return (len);
}

static int	get_split_len(char *str, int i)
{
	int	len;

	if (str[i] == '\0')
		return (0);
	if (str[i] == '|')
		return (1);
	if (str[i] == '>')
		return (1 + (str[i + 1] == '>'));
	if (str[i] == '<')
		return (1 + (str[i + 1] == '<'));
	len = get_split_len_process(str, i);
	if (str[i + len] != '\0'
		&& !is_white_space(str[i + len])
		&& !is_spec_char(str[i + len]))
		len += get_split_len(str, len + i);
	return (len);
}

static int	split_lexer_process(char **lex, char *str, int *lex_i, int *str_i)
{
	int		len;

	skip_white_space(str, str_i);
	if (str[*str_i] == '\0')
		return (1);
	len = get_split_len(str, *str_i);
	lex[*lex_i] = ft_calloc(len + 1, sizeof(char));
	if (lex[*lex_i] == NULL)
		return (0);
	ft_strlcpy(lex[*lex_i], str + *str_i, len + 1);
	(*lex_i)++;
	(*str_i) += len;
	return (1);
}

int	split_lexer(char **lex, char *str)
{
	int	str_i;
	int	lex_i;

	str_i = 0;
	lex_i = 0;
	while (str[str_i] != '\0')
	{
		if (split_lexer_process(lex, str, &lex_i, &str_i) == 0)
			return (0);
	}
	lex[lex_i] = NULL;
	return (1);
}
