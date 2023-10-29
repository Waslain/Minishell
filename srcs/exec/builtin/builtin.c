/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/29 13:12:08 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_child(t_data *data)
{
	const int	id = data->exec.id_child;
	char		*cmd;

	cmd = data->parser.cmds[id].cmd[0];
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| (ft_strcmp(cmd, "export") == 0 && data->nb_pipe > 0 \
			&& count_args((const char **)data->parser.cmds[id].cmd) == 1))
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
		|| (ft_strcmp(cmd, "export") == 0 && id == 0 && data->nb_cmd == 1))
		return (true);
	else
		return (false);
}

int	builtin_in_child(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	*cmd = data->parser.cmds[id].cmd[0];

	if (ft_strcmp((char *)cmd, "echo") == 0)
	{
		if (echo(data, id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp((char *)cmd, "pwd") == 0)
	{
		if (pwd(data, id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp((char *)cmd, "env") == 0)
	{
		if (env(data, id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp((char *)cmd, "export") == 0 && (export(data)))
		return (EXIT_FAILURE);
	else if (ft_strcmp((char *)cmd, "exit") == 0 && ft_exit_child(data))
		return (EXIT_FAILURE);
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
	else if (ft_strcmp(cmd, "cd") == 0)
	{
		if (cd(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		if (ft_exit(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	count_args(const char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
