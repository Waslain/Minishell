/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execsimplecommand(t_data *data)
{
	char	**paths;
	char	**cmd;
	char	*bin;

	cmd = ft_split(data->cmd, ' ');
	paths = get_paths(data);
	bin = get_bin(cmd[0], paths);
	execve(bin, cmd, data->envp);
	freeall(paths, cmd, bin);
}

void	execcommand(char *str, t_data *data)
{
	char	**paths;
	char	**cmd;
	char	*bin;

	cmd = ft_split(str, ' ');
	paths = get_paths(data);
	bin = get_bin(cmd[0], paths);
	execve(bin, cmd, data->envp);
	freeall(paths, cmd, bin);
}
