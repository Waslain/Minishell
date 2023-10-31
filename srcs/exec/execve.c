/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:15:50 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/31 15:43:19 by obouhlel         ###   ########.fr       */
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
void	no_run(const char **cmds, t_data *data)
{
	const char	*no_run[] = {"export", "cd", "unset", NULL};
	int			i;

	i = 0;
	while (no_run[i])
	{
		if (ft_strcmp((char *)cmds[0], (char *)no_run[i]) == 0)
		{
			if (i == EXPORT && count_args(cmds) > 1)
				return ;
			error_child(data, NULL, NULL, 0);
		}
		i++;
	}
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
void	ft_execve_bis(t_data *data, const char **cmds)
{
	static char	*cmd = NULL;
	char		*tmp;
	char		**path;
	int			i;

	tmp = ft_strjoin("/", cmds[0]);
	if (!tmp)
		return (error_child(data, NULL, NULL, 1));
	path = ft_get_path(data);
	if (!path)
		return (free(tmp), error_child(data, NULL, NULL, 1));
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], tmp);
		if (!cmd)
			return (free_tmp_and_path(tmp, path), malloc_error(data));
		if (access(cmd, X_OK) != -1)
			break ;
		ft_free((void **)&cmd);
	}
	free_tmp_and_path(tmp, path);
	if (!cmd)
		return ;
	return (execve(cmd, (char *const *)cmds, data->envp), free(cmd));
}

void	ft_execve(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	**cmds = (const char **)data->parser.cmds[id].cmd;

	if (is_in_child(data))
	{
		if (builtin_in_child(data) == EXIT_FAILURE)
			return (destroy_data(data, DESTROY_ENV), exit(EXIT_FAILURE));
		exit(0);
	}
	no_run(cmds, data);
	ft_execve_bis(data, cmds);
	if (access(cmds[0], X_OK) != -1)
	{
		if (ft_strncmp(cmds[0], "./", 2) == 0 || ft_strchr(cmds[0], '/') != 0)
			execve(cmds[0], (char *const *)cmds, data->envp);
		error_child(data, cmds[0], ": command not found", 127);
	}
	else
	{
		if (ft_strncmp("/", cmds[0], 1) == 0)
			error_child(data, cmds[0], ": No such file or directory", 127);
		error_child(data, cmds[0], ": command not found", 127);
	}
}
