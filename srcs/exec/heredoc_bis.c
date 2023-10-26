/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:08:16 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 11:42:16 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CTRL + C
// static
// void	finish_here_doc(t_heredoc heredoc, t_data *data)
// {
// 	free(heredoc.delimiter);
// 	ft_close(&heredoc.fd);
// 	destroy_data(data, DESTROY_ENV);
// 	exit(130);
// }

// CTRL + D
static
void	to_print_error(t_heredoc heredoc, t_data *data)
{
	// if (g_signal == 1)
	// {
	// 	destroy_data(data, DESTROY_ENV);
	// 	free(heredoc.delimiter);
	// 	ft_close(&heredoc.fd);
	// 	g_signal = 0;
	// 	exit(2);
	// }
	(void)data;
	ft_putstr_fd(HEREDOC_MSG_CTRL_D, 2);
	ft_putstr_fd(heredoc.delimiter, 2);
	ft_putendl_fd("')", 2);
}

static
void	end_of_heredoc(t_heredoc hd, t_data *data, t_heredoc *all_h, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free((void **)&all_h[i].name_file);
		ft_free((void **)&all_h[i].delimiter);
		i++;
	}
	free(all_h);
	free(data->to_free);
	data->to_free = NULL;
	destroy_data(data, DESTROY_ENV);
	ft_close(&hd.fd);
	exit(0);
}

void	runheredocchild(t_heredoc hd, t_data *data, t_heredoc *all_h, int size)
{
	char	*line;

	hd.fd = open(hd.name_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hd.fd == -1)
		return (error_child(data, hd.name_file, "heredoc error"));
	// while (!g_signal)
	while (1)
	{
		line = readline("heredoc > ");
		// if (!line || g_signal)
		if (!line || line[0] == 0)
		{
			to_print_error(hd, data);
			break ;
		}
		if (ft_strcmp(line, hd.delimiter) == 0)
			break ;
		ft_putendl_fd(line, hd.fd);
		ft_free((void **)&line);
	}
	// if (g_signal == 1)
	// 	finish_here_doc(heredoc, data);
	free(line);
	end_of_heredoc(hd, data, all_h, size);
}
