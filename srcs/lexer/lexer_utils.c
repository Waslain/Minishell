/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/29 13:42:25 by obouhlel         ###   ########.fr       */
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

	ptr = ft_calloc(sizeof(*ptr), (ft_strlen(src) + 1));
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
	char	*new_rl;
	int		len;

	len = ft_strlen(rl);
	new_rl = ft_calloc(sizeof(char), (len + 1) + 1);
	if (!new_rl)
		return (ft_free((void **)&rl), NULL);
	ft_strcpy(new_rl, rl);
	ft_free((void **)&rl);
	if (check_quote(new_rl) == 0)
		return (NULL);
	if (check_invalidchar(new_rl) == 0)
		return (ft_free((void **)&new_rl), NULL);
	new_rl = expandlex(data, new_rl);
	lex = lexer(data, new_rl);
	if (!lex)
		return (ft_free((void **)&new_rl), NULL);
	ft_free((void **)&new_rl);
	new_lex = clearquotes(lex);
	free_lexer(lex);
	return (new_lex);
}
