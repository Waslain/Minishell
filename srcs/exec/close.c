/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:08:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 10:02:47 by obouhlel         ###   ########.fr       */
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

void	close_all_pipe(int pipes[2][2])
{
	ft_close(&pipes[0][0]);
	ft_close(&pipes[0][1]);
	ft_close(&pipes[1][0]);
	ft_close(&pipes[1][1]);
}
