/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:13:05 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 13:12:04 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_size(void **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free((void **)&array[i]);
		i++;
	}
	free(array);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

void	ft_swap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (data->envp[i] && data->envp[i + 1])
			ft_swap((void **)&data->envp[i], (void **)&data->envp[i + 1]);
		i++;
	}
	free(data->envp[i - 1]);
	data->envp[i - 1] = NULL;
}

void	sort_envp(t_envp *envp, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(envp[j].key, envp[j + 1].key) > 0)
			{
				ft_swap((void **)&envp[j].key, (void **)&envp[j + 1].key);
				ft_swap((void **)&envp[j].value, (void **)&envp[j + 1].value);
			}
			j++;
		}
		i++;
	}
}
