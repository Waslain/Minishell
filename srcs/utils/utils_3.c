/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 12:57:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	freeall(char **cmd, char **paths, char *bin)
{
	ft_free(cmd);
	ft_free(paths);
	free(bin);
}

int	get_envp(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = ft_calloc(sizeof(char *), i + 2);
	if (!data->envp)
		return (EXIT_FAILURE);
	data->envp[0] = ft_strdup("?=0");
	i = 0;
	while (envp[i])
	{
		data->envp[i + 1] = ft_strdup(envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
