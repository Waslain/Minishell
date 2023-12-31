/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/29 12:15:32 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_data *data, const int id)
{
	const char	**cmds = (const char **)data->parser.cmds[id].cmd;
	const int	nb_args = count_args(cmds);
	int			i;
	int			ret;

	if (nb_args > 1)
	{
		ft_putendl_fd("env: too many arguments", STDERR);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (data->envp[i])
	{
		ret = ft_putendl_fd(data->envp[i], STDOUT);
		if (ret == -1)
			return (error_child(data, "env", ERROR_WRITE, 1), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
