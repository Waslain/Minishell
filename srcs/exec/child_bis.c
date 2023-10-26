/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:06:45 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 10:25:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	child_pipe_redir_first(t_data *data, int fd_in, int fd_out, int id)
{
	fd_in = open_infile(data->parser.redir[id].files, \
		data->parser.redir[id].nb_files, data);
	if (fd_in != NO_FILE)
	{
		if (dup2(fd_in, STDIN) == -1)
			return (error_child(data, "dup2", NULL));
		ft_close(&fd_in);
	}
	fd_out = open_outfile(data->parser.redir[id].files, \
		data->parser.redir[id].nb_files, data);
	if (fd_out != NO_FILE)
	{
		if (dup2(fd_out, STDOUT) == -1)
			return (error_child(data, "dup2", NULL));
		ft_close(&fd_out);
	}
	else
	{
		if (dup2(data->exec.pipes[id][WRITE], STDOUT) == -1)
			return (error_child(data, "dup2", NULL));
	}
}

static
void	child_pipe_redir_middle(t_data *data, int fd_in, int fd_out, int id)
{
	fd_in = open_infile(data->parser.redir[id].files, \
		data->parser.redir[id].nb_files, data);
	if (fd_in != NO_FILE)
	{
		if (dup2(fd_in, STDIN) == -1)
			return (error_child(data, "dup2", NULL));
		ft_close(&fd_in);
	}
	else if (dup2(data->exec.pipes[id - 1][READ], STDIN) == -1)
		return (error_child(data, "dup2", NULL));
	fd_out = open_outfile(data->parser.redir[id].files, \
		data->parser.redir[id].nb_files, data);
	if (fd_out != NO_FILE)
	{
		if (dup2(fd_out, STDOUT) == -1)
			return (error_child(data, "dup2", NULL));
		ft_close(&fd_out);
	}
	else if (dup2(data->exec.pipes[id][WRITE], STDOUT) == -1)
		return (error_child(data, "dup2", NULL));
}

static
void	child_pipe_redir_last(t_data *data, int fd_in, int fd_out, int id)
{
	fd_in = open_infile(data->parser.redir[id].files, \
		data->parser.redir[id].nb_files, data);
	if (fd_in != NO_FILE)
	{
		if (dup2(fd_in, STDIN) == -1)
			return (error_child(data, "dup2", NULL));
		ft_close(&fd_in);
	}
	else
	{
		if (dup2(data->exec.pipes[id - 1][READ], STDIN) == -1)
			return (error_child(data, "dup2", NULL));
	}
	fd_out = open_outfile(data->parser.redir[id].files, \
		data->parser.redir[id].nb_files, data);
	if (fd_out != NO_FILE)
	{
		if (dup2(fd_out, STDOUT) == -1)
			return (error_child(data, "dup2", NULL));
		ft_close(&fd_out);
	}
}

void	child_pipe_redir(t_data *data)
{
	const int	id = data->exec.id_child;
	int			fd_in;
	int			fd_out;

	fd_in = NO_FILE;
	fd_out = NO_FILE;
	if (id == 0)
		child_pipe_redir_first(data, fd_in, fd_out, id);
	else if (id == data->nb_cmd - 1)
		child_pipe_redir_last(data, fd_in, fd_out, id);
	else
		child_pipe_redir_middle(data, fd_in, fd_out, id);
	close_all_pipe(data->exec.pipes, data->nb_pipe);
	ft_execve(data);
}
