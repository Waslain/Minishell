/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:01:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 10:27:14 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_no_cmd_redir(t_data *data)
{
	int	i;

	data->exec.id_child = 0;
	while (data->exec.id_child < data->nb_pipe)
	{
		data->exec.pid[data->exec.id_child] = fork();
		if (data->exec.pid[data->exec.id_child] == -1)
			return (EXIT_FAILURE);
		if (data->exec.pid[data->exec.id_child] == 0)
			child_no_cmd_redir(data);
		i++;
	}
	i = -1;
	while (++i < data->nb_pipe)
		waitpid(data->exec.pid[i], &data->exec.status, 0);
	return (EXIT_SUCCESS);
}

int	parent_simple_cmd(t_data *data)
{
	data->exec.pid[0] = fork();
	if (data->exec.pid[0] == -1)
		return (EXIT_FAILURE);
	if (data->exec.pid[0] == 0)
	{
		ft_execve(data);
	}
	waitpid(data->exec.pid[0], &data->exec.status, 0);
	return (EXIT_SUCCESS);
}

int	parent_pipe(t_data *data)
{
	int	i;

	data->exec.id_child = 0;
	while (data->exec.id_child < data->nb_pipe)
	{
		data->exec.pid[data->exec.id_child] = fork();
		if (data->exec.pid[data->exec.id_child] == -1)
			return (EXIT_FAILURE);
		if (data->exec.pid[data->exec.id_child] == 0)
			child_pipe(data);
		i++;
	}
	close_all_pipe(data->exec.pipes);
	i = -1;
	while (++i < data->nb_pipe)
		waitpid(data->exec.pid[i], &data->exec.status, 0);
	return (EXIT_SUCCESS);
}

int	parent_pipe_redir(t_data *data)
{
	int	i;

	data->exec.id_child = 0;
	while (data->exec.id_child < data->nb_pipe)
	{
		data->exec.pid[data->exec.id_child] = fork();
		if (data->exec.pid[data->exec.id_child] == -1)
			return (EXIT_FAILURE);
		if (data->exec.pid[data->exec.id_child] == 0)
			child_pipe_redir(data);
		i++;
	}
	close_all_pipe(data->exec.pipes);
	i = -1;
	while (++i < data->nb_pipe)
		waitpid(data->exec.pid[i], &data->exec.status, 0);
	return (EXIT_SUCCESS);
}

int	parent_redir(t_data *data)
{
	data->exec.pid[0] = fork();
	if (data->exec.pid[0] == -1)
		return (EXIT_FAILURE);
	if (data->exec.pid[0] == 0)
		child_redir(data);
	waitpid(data->exec.pid[0], &data->exec.status, 0);
	return (EXIT_SUCCESS);
}
