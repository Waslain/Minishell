/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/27 19:53:17 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
bool	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static
bool	all_is_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static
void	ft_exit_bis(t_data *data, const char *arg)
{
	int	exit_code;

	exit_code = ft_atoi(arg);
	while (exit_code > 255)
		exit_code -= 256;
	destroy_data(data, DESTROY_ENV);
	exit(exit_code);
}

int	ft_exit(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	**cmds = (const char **)data->parser.cmds[id].cmd;
	const int	nb_args = count_args(cmds);

	ft_putendl_fd("exit", STDOUT);
	if (cmds[1] && !all_is_digit(cmds[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR);
		destroy_data(data, DESTROY_ENV);
		exit(2);
	}
	if (nb_args > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (EXIT_FAILURE);
	}
	else if (nb_args == 2)
		ft_exit_bis(data, cmds[1]);
	else
	{
		destroy_data(data, DESTROY_ENV);
		exit(0);
	}
	return (EXIT_SUCCESS);
}

int	ft_exit_child(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	**cmds = (const char **)data->parser.cmds[id].cmd;
	const int	nb_args = count_args(cmds);

	if (cmds[1] && !all_is_digit(cmds[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR);
	}
	if (nb_args > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
