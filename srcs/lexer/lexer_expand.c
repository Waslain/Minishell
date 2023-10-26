/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 15:11:11 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_to_end_var(char *lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (!ft_isalphanum(lex[i]) && lex[0] != '?')
			return (i);
		i++;
	}
	return (i);
}

char	*get_env_var(t_data *data, char *find)
{
	char	*path;
	int		i;
	int		x;

	if (!data || !data->envp || !find)
		return (NULL);
	i = 0;
	path = NULL;
	x = ft_strlen(find);
	while (data->envp[i])
	{
		path = ft_strnstr(data->envp[i], find, ft_strlen(data->envp[i]));
		if (path && data->envp[i][0] == find[0] && data->envp[i][x] == '=')
		{
			path = ft_substr(path, x + 1, ft_strlen(path));
			if (!path)
				return (malloc_error(data), NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_env_name(char *lex)
{
	int		i;
	char	*find;

	i = skip_to_end_var(lex);
	find = malloc(sizeof(char) * i + 1);
	if (!find)
		return (NULL);
	i = 0;
	while (lex[i])
	{
		if (ft_isalphanum(lex[i]) || (lex[0] == '?' && lex[1] != '?'))
		{
			find[i] = lex[i];
			i++;
		}
		else
			break ;
	}
	find[i] = '\0';
	return (find);
}

char	*expand_if_dollars_exec(t_data *data, char *lex, char *new_lex, int *i)
{
	char	*tmp;
	char	*find;
	char	*findval;

	find = get_env_name(&lex[*i + 1]);
	if (!find)
		return (malloc_error(data), NULL);
	findval = get_env_var(data, find);
	if (findval)
	{
		tmp = new_lex;
		new_lex = ft_strjoin(new_lex, findval);
		if (!new_lex)
			return (free(tmp), malloc_error(data), NULL);
		*i = *i + skip_to_end_var(&lex[*i + 1]) + 1;
		free_for_expand_all(tmp, find, findval);
	}
	else
	{
		*i = *i + skip_to_end_var(&lex[*i + 1]) + 1;
		free_for_expand(find, findval);
	}
	return (new_lex);
}

char	*expandlex(t_data *data, char *lex)
{
	int		i;
	char	*tmp;
	char	*new_lex;

	i = skip_to_dollars(lex) - 1;
	new_lex = ft_strndup(lex, i++);
	if (!new_lex)
		return (malloc_error(data), NULL);
	while (lex[i])
	{
		if (lex[i] == '$' && ft_isalphanum(lex[i + 1]))
			new_lex = expand_if_dollars_exec(data, lex, new_lex, &i);
		else
		{
			tmp = new_lex;
			new_lex = ft_strjoinn
				(new_lex, &lex[i], skip_to_dollars(&lex[i]) - 1);
			if (!new_lex)
				return (free(tmp), malloc_error(data), NULL);
			free(tmp);
			i = i + skip_to_dollars(&lex[i]);
		}
	}
	return (ft_free((void **)&lex), new_lex);
}
