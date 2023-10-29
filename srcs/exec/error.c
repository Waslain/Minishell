/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:33:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 09:47:19 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_child(t_data *data, const char *arg, const char *msg, int val)
{
	if (arg && !msg)
	{
		ft_putstr_fd("minishell: ", STDERR);
		perror(arg);
	}
	else if (arg && msg)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd((char *)arg, STDERR);
		ft_putstr_fd((char *)msg, STDERR);
		ft_putstr_fd("\n", STDERR);
	}
	destroy_data(data, DESTROY_ENV);
	if (val == -1)
		exit(errno);
	else
		exit(val);
}

void	error_fork(t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd("fork: ", STDERR);
	ft_putstr_fd(strerror(errno), STDERR);
	ft_putstr_fd("\n", STDERR);
	destroy_data(data, DESTROY_ENV);
	exit(EXIT_FAILURE);
}

void	error_pipes(int ***pipes, int index, t_data *data)
{
	int	i;

	i = 0;
	while (i < index)
	{
		ft_close(&(*pipes)[i][0]);
		ft_close(&(*pipes)[i][1]);
		i++;
	}
	i = 0;
	while (i < index)
	{
		free((*pipes)[i]);
		i++;
	}
	free(*pipes);
	*pipes = NULL;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd("pipes: ", STDERR);
	ft_putstr_fd(strerror(errno), STDERR);
	ft_putstr_fd("\n", STDERR);
	destroy_data(data, DESTROY_ENV);
	exit(EXIT_FAILURE);
}

void	malloc_error_exec(t_data *data)
{
	if (data->nb_pipe > 0)
		close_all_pipe(data->exec.pipes, data->nb_pipe);
	malloc_error(data);
}
