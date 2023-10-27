/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:43:32 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 10:50:32 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str && *str != (char)c)
		str++;
	if (*str == (char)c)
		return (str);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static
size_t	ft_strsize(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
	{
		size++;
		return (size);
	}
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*nstr;
	size_t		size;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	size = ft_strsize(n);
	nstr = (char *)malloc((size + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	nstr[size] = 0;
	if (n == 0)
		nstr[0] = '0';
	if (n < 0)
		nstr[0] = '-';
	while (n)
	{
		if (n > 0)
			nstr[size - 1] = (n % 10) + 48;
		else
			nstr[size - 1] = (-n % 10) + 48;
		n /= 10;
		size--;
	}
	return (nstr);
}

bool	ft_isalphanum(int c)
{
	if (ft_isalpha(c) || (c <= '9' && c >= '0'))
		return (true);
	return (false);
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
