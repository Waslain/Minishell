/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:08:16 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 16:57:42 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_signal;

void	free_heredoc(t_heredoc *heredoc, int nb_heredoc)
{
	int	i;

	i = 0;
	while (i < nb_heredoc)
	{
		ft_free((void **)&heredoc[i].name_file);
		i++;
	}
	ft_free((void **)&heredoc);
}

// CTRL + C
static
void	finish_here_doc(t_heredoc hd, t_data *data)
{
	ft_close(&hd.fd);
	destroy_data(data, DESTROY_ENV);
	exit(130);
}

// CTRL + D
static
void	to_print_error(t_heredoc heredoc, t_data *data)
{
	ft_putstr_fd(HEREDOC_MSG_CTRL_D, 2);
	ft_putstr_fd(heredoc.delimiter, 2);
	ft_putendl_fd("')", 2);
	destroy_data(data, DESTROY_ENV);
	exit(0);
}

static
void	end_of_heredoc(t_heredoc hd, t_data *data)
{
	ft_close(&hd.fd);
	free_array(data->to_free);
	data->to_free = NULL;
	destroy_data(data, DESTROY_ENV);
	exit(0);
}

void	run_heredoc_child(t_heredoc hd, t_data *data)
{
	char	*line;

	hd.fd = open(hd.name_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hd.fd == -1)
		return (error_child(data, hd.name_file, ": heredoc error", 1));
	while (!g_signal)
	{
		line = readline("heredoc > ");
		if (!line || line[0] == 0 || g_signal)
		{
			to_print_error(hd, data);
			break ;
		}
		if (ft_strcmp(line, hd.delimiter) == 0)
			break ;
		ft_putendl_fd(line, hd.fd);
		ft_free((void **)&line);
	}
	if (g_signal == 1)
		finish_here_doc(hd, data);
	free(line);
	end_of_heredoc(hd, data);
}
