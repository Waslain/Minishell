/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_options(char **cmd, int i)
{
	if (!cmd[i] || cmd[i][0] != '-' || cmd[i][1] != 'n')
		return (0);
	return (1);
}

void	builtin_echo(char **str)
{
	char	**cmd;
	int		i;
	int		x;

	cmd = str;
	i = 1;
	if (check_options(cmd, i) == 1)
		i++;
	while (cmd[i])
	{
		x = 0;
		while (cmd[i][x])
		{
			write(1, &cmd[i][x], 1);
			x++;
		}
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (check_options(cmd, 1) != 1)
		write(1, "\n", 1);
	// printf("builtin_echo\n");
	// ft_free(cmd);
}
