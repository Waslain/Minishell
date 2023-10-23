/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
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

t_data	*get_envp(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = ft_calloc(sizeof(char *), i + 2);
	data->envp[0] = ft_strdup("?=0");
	i = 0;
	while (envp[i])
	{
		data->envp[i + 1] = ft_strdup(envp[i]);
		i++;
	}
	return (data);
}

void	ft_error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
