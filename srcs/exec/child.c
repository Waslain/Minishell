/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:15:19 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 08:58:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_no_cmd_redir(t_data *data)
{
	(void)data;
}

void	child_pipe(t_data *data)
{
	const int	id = data->exec.id_child;

	if (id == 0)
	{
		if (dup2(data->exec.pipes[id][WRITE], STDOUT) == -1)
			return (error_child(data, "dup2", NULL));
	}
	else if (id == data->nb_cmd - 1)
	{
		if (dup2(data->exec.pipes[id - 1][READ], STDIN) == -1)
			return (error_child(data, "dup2", NULL));
	}
	else
	{
		if (dup2(data->exec.pipes[id - 1][READ], STDIN) == -1)
			return (error_child(data, "dup2", NULL));
		if (dup2(data->exec.pipes[id][WRITE], STDOUT) == -1)
			return (error_child(data, "dup2", NULL));
	}
	close_all_pipe(data->exec.pipes, data->nb_pipe);
	ft_execve(data);
}

void	child_pipe_redir(t_data *data)
{
	(void)data;
}

void	child_redir(t_data *data)
{
	(void)data;
}
