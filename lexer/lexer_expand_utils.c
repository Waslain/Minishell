/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_to_dollars(char *lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (lex[i] != '$')
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_strjoinn(char const *s1, char const *s2, int n)
{
	char	*result;
	int		i;
	int		y;

	i = 0;
	y = 0;
	result = malloc(sizeof(char) * ft_strlen(s1) + n + 2);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[y] && y <= n)
	{
		result[i] = s2[y];
		i++;
		y++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strndup(const char *src, int x)
{
	char	*ptr;
	int		n;

	ptr = malloc(sizeof(*ptr) * (x + 2));
	n = 0;
	while (src[n] && n <= x)
	{
		ptr[n] = src[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}

void	free_for_expand(char *find, char *findval)
{
	free(find);
	free(findval);
}

void	free_for_expand_all(char *tmp, char *find, char *findval)
{
	free(find);
	free(findval);
	free(tmp);
}
