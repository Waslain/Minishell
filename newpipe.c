/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/02/24 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newpipe(t_data *data)
{
	int	i;

	i = 0;
	data->pipe = malloc(sizeof(data->pipe) * (data->nb_cmd));
	if (data->pipe == NULL)
		ft_error("Pipe Alloc Error");
	while (i < (data->nb_cmd - 1))
	{
		data->pipe[i] = malloc(sizeof(int) * 2);
		if (data->pipe[i] == NULL)
			ft_error("Pipe Alloc Error");
		pipe(data->pipe[i]);
		i++;
	}
}

void	close_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipe[i])
	{
		close(*data->pipe[i]);
		free(data->pipe[i]);
		i++;
	}
	free(data->pipe);
}
