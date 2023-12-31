/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:01:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/11/02 05:27:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_no_cmd_redir(t_data *data)
{
	int	i;	

	while (data->exec.id_child < (data->nb_pipe + 1))
	{
		data->exec.pid[data->exec.id_child] = fork();
		if (data->exec.pid[data->exec.id_child] == -1)
			return (error_fork(data), EXIT_FAILURE);
		if (data->exec.pid[data->exec.id_child] == 0)
		{
			mode_signal(S_CHILD);
			child_no_cmd_redir(data);
		}
		data->exec.id_child++;
	}
	i = -1;
	while (++i < (data->nb_pipe + 1))
		waitpid(data->exec.pid[i], &data->exec.status, WUNTRACED);
	return (EXIT_SUCCESS);
}

int	parent_simple_cmd(t_data *data)
{
	int	ret;

	if (is_in_parent(data) == true)
	{
		ret = builtin_in_parent(data);
		if (ret)
			return (ret);
	}
	else
	{
		data->exec.pid[0] = fork();
		if (data->exec.pid[0] == -1)
			return (error_fork(data), EXIT_FAILURE);
		if (data->exec.pid[0] == 0)
		{
			mode_signal(S_CHILD);
			ft_execve(data);
		}
		waitpid(data->exec.pid[0], &data->exec.status, WUNTRACED);
		update_status_with_signal(&data->exec.status);
	}
	return (EXIT_SUCCESS);
}

int	parent_redir(t_data *data)
{
	if (is_in_parent(data) == true)
	{
		if (builtin_in_parent(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		data->exec.pid[0] = fork();
		if (data->exec.pid[0] == -1)
			return (error_fork(data), EXIT_FAILURE);
		if (data->exec.pid[0] == 0)
		{
			mode_signal(S_CHILD);
			child_redir(data);
		}
		waitpid(data->exec.pid[0], &data->exec.status, WUNTRACED);
		update_status_with_signal(&data->exec.status);
	}
	return (EXIT_SUCCESS);
}

int	parent_pipe(t_data *data)
{
	int	i;

	while (data->exec.id_child < data->nb_cmd)
	{
		data->exec.pid[data->exec.id_child] = fork();
		if (data->exec.pid[data->exec.id_child] == -1)
			return (error_fork(data), EXIT_FAILURE);
		if (data->exec.pid[data->exec.id_child] == 0)
		{
			mode_signal(S_CHILD);
			child_pipe(data);
		}
		data->exec.id_child++;
	}
	close_all_pipe(data->exec.pipes, data->nb_pipe);
	i = -1;
	while (++i < data->nb_cmd)
		waitpid(data->exec.pid[i], &data->exec.status, WUNTRACED);
	update_status_with_signal(&data->exec.status);
	return (EXIT_SUCCESS);
}

int	parent_pipe_redir(t_data *data)
{
	int	i;

	while (data->exec.id_child < data->nb_cmd)
	{
		data->exec.pid[data->exec.id_child] = fork();
		if (data->exec.pid[data->exec.id_child] == -1)
			return (error_fork(data), EXIT_FAILURE);
		if (data->exec.pid[data->exec.id_child] == 0)
		{
			mode_signal(S_CHILD);
			child_pipe_redir(data);
		}
		data->exec.id_child++;
	}
	close_all_pipe(data->exec.pipes, data->nb_pipe);
	i = -1;
	while (++i < data->nb_cmd)
		waitpid(data->exec.pid[i], &data->exec.status, WUNTRACED);
	update_status_with_signal(&data->exec.status);
	return (EXIT_SUCCESS);
}
