/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:29:03 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 14:57:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	**cmd = (const char **)data->parser.cmds[id].cmd;
	int			i;
	char		*ret;

	i = 1;
	while (cmd[i])
	{
		ret = found_value_with_key(data->exec.envp_s, (char *)cmd[i], \
								data->exec.size);
		if (ret && ft_strcmp((char *)cmd[i], "?") != 0 && \
					ft_strcmp((char *)cmd[i], "_") != 0)
		{
			if (delete_key_value(&data->exec.envp_s, &data->exec.size, \
									(char *)cmd[i]))
				return (malloc_error(data), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
