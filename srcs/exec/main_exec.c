/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/31 15:31:44 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	init_exec(t_data *data)
{
	int	i;

	data->exec.to_free = NULL;
	data->exec.id_child = 0;
	data->exec.pid = ft_calloc(sizeof(pid_t), data->nb_pipe + 1);
	if (!data->exec.pid)
		return (EXIT_FAILURE);
	if (data->nb_cmd > 0 && data->nb_pipe > 0)
	{
		data->exec.pipes = ft_calloc(sizeof(int *), data->nb_pipe);
		if (!data->exec.pipes)
			return (EXIT_FAILURE);
		i = -1;
		while (++i < data->nb_pipe)
		{
			data->exec.pipes[i] = ft_calloc(sizeof(int), 2);
			if (!data->exec.pipes[i])
				return (error_pipes(&data->exec.pipes, i, data), 1);
			if (pipe(data->exec.pipes[i]) == -1)
				return (error_pipes(&data->exec.pipes, i, data), 1);
		}
	}
	return (EXIT_SUCCESS);
}

void	update_exit_code(t_data *data, int status)
{
	char			*exit_code;

	while (status > 255)
		status -= 255;
	exit_code = ft_itoa(status);
	if (!exit_code)
		return (malloc_error(data));
	if (update_value_with_key(data->exec.envp_s, &data->exec.size, "?", \
		exit_code))
		return (free(exit_code), malloc_error(data));
	ft_free((void **)&exit_code);
}

static
void	update_shlvl(t_data *data)
{
	char	*shlvl;
	int		shlvl_int;

	shlvl = found_value_with_key(data->exec.envp_s, "SHLVL", data->exec.size);
	if (!shlvl)
	{
		if (add_key_value(&data->exec.envp_s, &data->exec.size, "SHLVL", \
			"1"))
			return (malloc_error_exec(data));
		if (conv_env_struct_to_env(&data->envp, data->exec.envp_s, \
								data->exec.size))
			return (malloc_error_exec(data));
		return ;
	}
	shlvl_int = ft_atoi(shlvl);
	shlvl_int++;
	shlvl = ft_itoa(shlvl_int);
	if (!shlvl)
		return (malloc_error_exec(data));
	if (update_value_with_key(data->exec.envp_s, &data->exec.size, "SHLVL", \
		shlvl))
		return (free(shlvl), malloc_error_exec(data));
	if (conv_env_struct_to_env(&data->envp, data->exec.envp_s, data->exec.size))
		return (malloc_error_exec(data));
	ft_free((void **)&shlvl);
}

static
void	exec(t_data *data)
{
	int	status;

	status = EXIT_SUCCESS;
	if (data->nb_cmd == 0 && data->nb_redir > 0)
		status = parent_no_cmd_redir(data);
	else if (data->nb_pipe == 0 && data->nb_redir == 0)
		status = parent_simple_cmd(data);
	else if (data->nb_pipe > 0 && data->nb_redir == 0)
		status = parent_pipe(data);
	else if (data->nb_pipe == 0 && data->nb_cmd == 1 && data->nb_redir > 0)
		status = parent_redir(data);
	else if (data->nb_pipe > 0 && data->nb_redir > 0)
		status = parent_pipe_redir(data);
	if (status != 0)
		update_exit_code(data, status);
	else
		update_exit_code(data, data->exec.status);
}

int	main_exec(t_data *data)
{
	static bool	first = true;

	if (init_exec(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data->exec.envp_s == NULL)
	{
		if (conv_env_to_struct(data->envp, &data->exec.envp_s, \
								&data->exec.size))
			return (malloc_error_exec(data), EXIT_FAILURE);
	}
	if (first)
	{
		first = false;
		update_shlvl(data);
	}
	swap_env(data);
	exec(data);
	if (conv_env_struct_to_env(&data->envp, data->exec.envp_s, data->exec.size))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
