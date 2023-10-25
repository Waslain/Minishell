/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/25 12:47:00 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_until_quote(const char *src, char *ptr, int *n, int *i)
{
	(*n)++;
	while (src[*n])
	{
		if (src[*n] == '\'')
		{
			(*n)++;
			break ;
		}
		else
		{
			ptr[*i] = src[*n];
			(*i)++;
			(*n)++;
		}
	}
}

void	dup_until_dquote(const char *src, char *ptr, int *n, int *i)
{
	(*n)++;
	while (src[*n])
	{
		if (src[*n] == '"')
		{
			(*n)++;
			break ;
		}
		else
		{
			ptr[*i] = src[*n];
			(*i)++;
			(*n)++;
		}
	}
}

char	*ft_strdupnoquote(const char *src)
{
	char	*ptr;
	int		n;
	int		i;

	ptr = malloc(sizeof(*ptr) * (ft_strlen(src) + 1));
	if (!ptr)
		return (NULL);
	n = 0;
	i = 0;
	while (src[n])
	{
		if (src[n] == '\'')
			dup_until_quote(src, ptr, &n, &i);
		else if (src[n] == '"')
			dup_until_dquote(src, ptr, &n, &i);
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
	lex = lexer(data, rl);
	free(rl);
	new_lex = clearquotes(lex);
	free_lexer(lex);
	return (new_lex);
}
