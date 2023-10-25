/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:15:50 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 10:26:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data)
{
	(void)data;
}

// // the main execution child process
// void	ft_shell_child(t_shell *shell)
// {
// 	const int	n = shell->id_child;

// 	if ((ft_strncmp("./", shell->args[n][0], 2) == 0 && 
// 		access(shell->args[n][0], X_OK) != FAILURE) || 
// 		ft_strchr(shell->args[n][0], '/') != NULL)
// 	{
// 		execve(shell->args[n][0], shell->args[n], shell->env);
// 		ft_msg(shell, shell->args[n][0], errno, &exit);
// 	}
// 	ft_shell_child_bis(shell, n);
// }

// // the main execution child process bis
// void	ft_shell_child_bis(t_shell *shell, const int n)
// {
// 	char	*tmp;
// 	char	*cmd;
// 	char	**path;

// 	path = ft_get_path(shell);
// 	tmp = ft_strjoin("/", shell->args[n][0]);
// 	if (!tmp)
// 		return (free_array_strs(path), ft_msg(shell, NULL, MA, &exit));
// 	cmd = ft_access(tmp, path);
// 	if (!cmd)
// 		return (free_array_strs(path), free(tmp),
//	ft_msg(shell, NULL, MA, &exit));
// 	if (cmd == FAIL && !ft_strcmp("exit", shell->args[n][0]))
// 		return (free_array_strs(path), free(tmp), 
// 				ft_msg(shell, shell->args[n][0], EX, &exit));
// 	if (cmd == FAIL)
// 		return (free_array_strs(path), free(tmp), 
// 				ft_msg(shell, shell->args[n][0], CM, &exit));
// 	execve(cmd, shell->args[n], shell->env);
// 	exit(EXIT_FAILURE);
// }
