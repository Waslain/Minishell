/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/27 20:17:05 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_free((void **)&tab[i]);
		i++;
	}
	free(tab);
}

static
int	get_envp_bis(t_data *data, char **envp, int mode)
{
	int	i;

	i = -1;
	if (mode == 2)
	{
		data->envp[0] = ft_strdup("?=0");
		if (!data->envp[0])
			return (EXIT_FAILURE);
		while (envp[++i])
		{
			data->envp[i + 1] = ft_strdup(envp[i]);
			if (!data->envp[i + 1])
				return (free_array_size((void **)data->envp, ++i), 1);
		}
	}
	else
	{
		while (envp[++i])
		{
			data->envp[i] = ft_strdup(envp[i]);
			if (!data->envp[i])
				return (free_array_size((void **)data->envp, i), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	get_envp(t_data *data, char **envp)
{
	int		size;
	int		add;

	if (envp != NULL && envp[0] != NULL && envp[0][0] == '?')
		add = 1;
	else
		add = 2;
	size = count_args((const char **)envp);
	data->envp = ft_calloc(sizeof(char *), size + add);
	if (!data->envp)
		return (EXIT_FAILURE);
	if (get_envp_bis(data, envp, add) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
