/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 09:32:29 by obouhlel         ###   ########.fr       */
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

void	freeall(char **cmd, char **paths, char *bin)
{
	free_array(cmd);
	free_array(paths);
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
