/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:08:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 09:43:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -2;
	}
}

void	close_all_pipe(int **pipes, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		ft_close(&pipes[i][0]);
		ft_close(&pipes[i][1]);
		i++;
	}
}
