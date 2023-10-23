/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_data *data, char *cmd, char **str)
{
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(str);
	else if (ft_strcmp(cmd, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		builtin_env(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit();
	return (1);
}
