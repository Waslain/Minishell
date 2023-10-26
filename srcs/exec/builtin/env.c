/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 13:26:31 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_data *data, const int id)
{
	int	i;
	int	ret;

	(void)id;
	i = 1;
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '=') != NULL)
		{
			ret = ft_putendl_fd(data->envp[i], STDOUT);
			if (ret == -1)
				return (error_child(data, "env", ERROR_WRITE, 1), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
