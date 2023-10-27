/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:15:50 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 10:48:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	free_tmp_and_path(char *tmp, char **path)
{
	if (tmp)
		ft_free((void **)&tmp);
	if (path)
		free_array(path);
}

static
char	**ft_get_path(t_data *data)
{
	char	**path;
	char	*tmp;

	tmp = found_value_with_key(data->exec.envp_s, "PATH", data->exec.size);
	if (!tmp)
	{
		path = ft_calloc(sizeof(char *), 1);
		if (!path)
			return (malloc_error(data), NULL);
		path[0] = NULL;
		return (path);
	}
	path = ft_split(tmp, ':');
	if (!path)
		return (malloc_error(data), NULL);
	return (path);
}

static
void	ft_execve_bis(t_data *data, const char **cmds, char **path, char *tmp)
{
	static char	*cmd = NULL;
	int			i;

	if (path)
	{
		i = -1;
		while (path[++i])
		{
			cmd = ft_strjoin(path[i], tmp);
			if (!cmd)
				return (free_tmp_and_path(tmp, path), malloc_error(data));
			errno = 0;
			if (access(cmd, X_OK) != -1)
				break ;
			ft_free((void **)&cmd);
		}
		free_tmp_and_path(tmp, path);
	}
	if (!cmd)
	{
		cmd = ft_strdup(cmds[0]);
		if (!cmd)
			return (free_tmp_and_path(tmp, path), malloc_error(data));
	}
	return (execve(cmd, (char *const *)cmds, data->envp), free(cmd));
}

void	ft_execve(t_data *data)
{
	const int	n = data->exec.id_child;
	const char	**cmds = (const char **)data->parser.cmds[n].cmd;
	char		**path;
	char		*tmp;

	if (is_in_child(data))
	{
		if (builtin_in_child(data) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		exit(0);
	}
	if ((ft_strncmp("./", cmds[0], 2) == 0 && access(cmds[0], X_OK) != -1))
	{
		execve(cmds[0], (char *const *)cmds, data->envp);
		error_child(data, cmds[0], ": command not found", 127);
	}
	path = ft_get_path(data);
	if (!path)
		return (error_child(data, NULL, NULL, 1));
	tmp = ft_strjoin("/", cmds[0]);
	if (!tmp)
		return (free_array(path), error_child(data, NULL, NULL, 1));
	ft_execve_bis(data, cmds, path, tmp);
	error_child(data, cmds[0], ": command not found", 127);
}
