/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 17:39:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	init_exec(t_data *data)
{
	int	i;

	data->exec.id_child = 0;
	data->exec.pid = ft_calloc(sizeof(pid_t), data->nb_pipe + 1);
	if (!data->exec.pid)
		return (EXIT_FAILURE);
	i = -1;
	if (data->nb_pipe > 0)
	{
		while (++i < 2)
			if (pipe(data->exec.pipes[i]) == -1)
				return (EXIT_FAILURE);
	}
	if (conv_env_to_struct(data->envp, &data->exec.envp_s, &data->exec.size))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static
void	update_exit_code(t_data *data)
{
	char			*exit_code;

	while (data->exec.status > 255)
		data->exec.status -= 255;
	exit_code = ft_itoa(data->exec.status);
	if (!exit_code)
		return (malloc_error(data));
	update_value_with_key(data->exec.envp_s, &data->exec.size, "?", exit_code);
	ft_free((void **)&exit_code);
}

int	main_exec(t_data *data)
{
	int	status;

	if (init_exec(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = EXIT_SUCCESS;
	// if (data->nb_cmd == 0 && data->nb_redir > 0)
	// 	status = parent_no_cmd_redir(data);
	if (data->nb_pipe == 0 && data->nb_redir == 0)
		status = parent_simple_cmd(data);
	// else if (data->nb_pipe > 0 && data->nb_redir == 0)
	// 	status = parent_pipe(data);
	// else if (data->nb_pipe > 0 && data->nb_redir > 0)
	// 	status = parent_pipe_redir(data);
	// else if (data->nb_pipe == 0 && data->nb_cmd == 1 && data->nb_redir > 0)
	// 	status = parent_redir(data);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	update_exit_code(data);
	if (conv_env_struct_to_env(&data->envp, data->exec.envp_s, data->exec.size))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
