/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:11:52 by fduzant           #+#    #+#             */
/*   Updated: 2022/05/05 12:11:53 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_is_charset(char str, char charset)
{
	if (str == charset)
		return (1);
	return (0);
}

static int	ft_wordlen(char const *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_charset(str[i], charset) == 0)
		i++;
	return (i);
}

static int	ft_wordcount(char const *str, char charset)
{
	int	i;
	int	w;

	w = 0;
	while (*str)
	{
		while (*str && ft_is_charset(*str, charset) == 1)
			str++;
		i = ft_wordlen(str, charset);
		str += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_splitdup(char const *src, int wl)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((wl + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (src[i] && i < wl)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	**ft_split(char const *str, char charset)
{
	char	**dest;
	int		i;
	int		y;
	int		size;

	i = 0;
	size = ft_wordcount(str, charset);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (0);
	while (i < size)
	{
		while (ft_is_charset(*str, charset))
			str++;
		y = ft_wordlen(str, charset);
		dest[i] = ft_splitdup(str, y);
		str += y;
		i++;
	}
	dest[size] = 0;
	return (dest);
}
