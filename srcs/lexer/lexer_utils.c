/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(const char *src, int n, int x)
{
	if (src[0] == '\'' && n == 0)
		return (1);
	if (src[0] == '"' && n == 0)
		return (1);
	if (src[x] == '\'' && n == x)
		return (1);
	if (src[x] == '"' && n == x)
		return (1);
	return (0);
}

char	*ft_strdupnoquote(const char *src)
{
	char	*ptr;
	int		n;
	int		i;
	int		x;

	n = 0;
	while (src[n])
		n++;
	x = n - 1;
	ptr = malloc(sizeof(*ptr) * (n + 1));
	n = 0;
	i = 0;
	while (src[n])
	{
		if (skip_quotes(src, n, x) == 1)
			n++;
		else
		{
			ptr[i] = src[n];
			i++;
			n++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**clearquotes(char **lex)
{
	char	**new_lex;
	int		i;

	i = 0;
	while (lex[i])
		i++;
	new_lex = ft_calloc(sizeof(char *), i + 1);
	if (!new_lex)
		return (0);
	i = 0;
	while (lex[i])
	{
		new_lex[i] = ft_strdupnoquote(lex[i]);
		i++;
	}
	return (new_lex);
}

char	**clear_lex(t_data *data, char *rl)
{
	char	**lex;
	char	**new_lex;

	rl = expandlex(data, rl);
	lex = lexer(rl);
	free(rl);
	new_lex = clearquotes(lex);
	free_lexer(lex);
	return (new_lex);
}
