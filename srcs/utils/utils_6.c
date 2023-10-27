/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:16:07 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 14:54:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
bool	is_whitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	return (NULL);
}

int	count_type_token(t_lexer *lexer, int type)
{
	int	nb;

	nb = 0;
	while (lexer)
	{
		if (lexer->type == type)
			nb++;
		lexer = lexer->next;
	}
	return (nb);
}

int	count_nb_redir(t_lexer *lexer)
{
	int	nb_redir;

	nb_redir = 0;
	while (lexer)
	{
		if (lexer->type == REDIR_IN || lexer->type == REDIR_OUT
			|| lexer->type == APPEND_IN || lexer->type == APPEND_OUT)
			nb_redir++;
		lexer = lexer->next;
	}
	return (nb_redir);
}
