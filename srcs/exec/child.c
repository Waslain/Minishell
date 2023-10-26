/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:15:19 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 12:17:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_no_cmd_redir(t_data *data)
{
	int	fd_in;
	int	fd_out;
	int	i;

	i = 0;
	while (i < data->parser.size_redir)
	{
		fd_in = open_infile(data->parser.redir[i].files, \
					data->parser.redir[i].nb_files, data);
		fd_out = open_outfile(data->parser.redir[i].files, \
					data->parser.redir[i].nb_files, data);
		if (fd_in != NO_FILE)
			ft_close(&fd_in);
		if (fd_out != NO_FILE)
			ft_close(&fd_out);
		i++;
	}
	destroy_data(data, DESTROY_ENV);
	exit(0);
}

void	child_pipe(t_data *data)
{
	const int	id = data->exec.id_child;

	if (id == 0)
	{
		if (dup2(data->exec.pipes[id][WRITE], STDOUT) == -1)
			return (error_child(data, "dup2", NULL, -1));
	}
	else if (id == data->nb_cmd - 1)
	{
		if (dup2(data->exec.pipes[id - 1][READ], STDIN) == -1)
			return (error_child(data, "dup2", NULL, -1));
	}
	else
	{
		if (dup2(data->exec.pipes[id - 1][READ], STDIN) == -1)
			return (error_child(data, "dup2", NULL, -1));
		if (dup2(data->exec.pipes[id][WRITE], STDOUT) == -1)
			return (error_child(data, "dup2", NULL, -1));
	}
	close_all_pipe(data->exec.pipes, data->nb_pipe);
	ft_execve(data);
}

void	child_redir(t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = open_infile(data->parser.redir[0].files, \
				data->parser.redir[0].nb_files, data);
	if (fd_in != NO_FILE)
	{
		if (dup2(fd_in, STDIN) == -1)
			return (ft_close(&fd_in), error_child(data, "dup2", NULL, -1));
		ft_close(&fd_in);
	}
	fd_out = open_outfile(data->parser.redir[0].files, \
				data->parser.redir[0].nb_files, data);
	if (fd_out != NO_FILE)
	{
		if (dup2(fd_out, STDOUT) == -1)
			return (ft_close(&fd_out), error_child(data, "dup2", NULL, -1));
		ft_close(&fd_out);
	}
	ft_execve(data);
}
