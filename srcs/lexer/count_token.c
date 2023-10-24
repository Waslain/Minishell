/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 12:48:26 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_special_char(char *str, int *i, int *nb_token)
{
	(*nb_token)++;
	if (str[*i] == '>' && str[*i + 1] == '>')
		(*i) += 2;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		(*i) += 2;
	else
		(*i)++;
}

static int	process(char *str, int *i, int	*nb_token)
{
	skip_white_space(str, i);
	if ((str[*i] == '\'') || (str[*i] == '"'))
	{
		(*i)++;
		go_next_quote(str, i, str[(*i) - 1]);
		if (str[*i] == '\0')
			return (-1);
		(*i)++;
		if (str[*i] == '\0' || is_white_space(str[*i]) \
							|| is_spec_char(str[*i]))
			(*nb_token)++;
	}
	else if (is_spec_char(str[*i]))
		process_special_char(str, i, nb_token);
	else if (str[*i] != '\0')
	{
		skip_token(str, i);
		if (str[*i] == '\0' || is_white_space(str[*i]) \
							|| is_spec_char(str[*i]))
			(*nb_token)++;
	}
	return (0);
}

int	count_token(char *str)
{
	int	nb_token;
	int	i;
	int	res;

	nb_token = 0;
	i = 0;
	while (str[i] != '\0')
	{
		res = process(str, &i, &nb_token);
		if (res != 0)
			return (res);
	}
	return (nb_token);
}
