/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 14:42:31 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (true);
	else
		return (false);
}

bool	is_in_child(t_data *data)
{
	const int	id = data->exec.id_child;
	char		*cmd;

	cmd = data->parser.cmds[id].cmd[0];
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| (ft_strcmp(cmd, "export") == 0 && id != 0 && data->nb_pipe != 0))
		return (true);
	else
		return (false);
}

bool	is_in_parent(t_data *data)
{
	const int	id = data->exec.id_child;
	char		*cmd;

	cmd = data->parser.cmds[id].cmd[0];
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| (ft_strcmp(cmd, "export") == 0 && id == 0 && data->nb_cmd == 0))
		return (true);
	else
		return (false);
}

int	builtin_in_child(t_data *data)
{
	const int	id = data->exec.id_child;
	char		*cmd;

	cmd = data->parser.cmds[id].cmd[0];
	if (ft_strcmp(cmd, "echo") == 0)
	{
		if (echo(data, id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		if (pwd(data, id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		if (env(data, id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		if (export(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (destroy_data(data, DESTROY_ENV), EXIT_SUCCESS);
}

int	builtin_in_parent(t_data *data)
{
	const int	id = data->exec.id_child;
	char		*cmd;

	cmd = data->parser.cmds[id].cmd[0];
	if (ft_strcmp(cmd, "export") == 0)
	{
		if (export(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		if (unset(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	// else if (ft_strcmp(cmd, "cd") == 0)
	// {
	// 	if (cd(data, id) == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);
	// }
	// else if (ft_strcmp(cmd, "exit") == 0)
	// {
	// 	if (exit(data) == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}
