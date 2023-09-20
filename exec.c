/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/02/24 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bin(char *cmd, char **paths)
{
	char	*tmp;
	char	*ret_path;
	int		i;

	tmp = NULL;
	ret_path = NULL;
	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	while (paths[i++])
	{
		if (!paths[i])
			return (NULL);
		tmp = ft_strjoin(paths[i], "/");
		ret_path = ft_strjoin(tmp, cmd);
		if (access(ret_path, F_OK) == 0)
			return (free(tmp), ret_path);
		free(tmp);
		free(ret_path);
	}
	ft_error("Command not found\n");
	return (NULL);
}

char	*get_line(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data->envp[i++])
	{
		path = ft_strnstr(data->envp[i], "PATH=", ft_strlen(data->envp[i]));
		if (path && data->envp[i][0] == 'P' && data->envp[i][5] == '/')
		{
			path = ft_substr(path, 5, ft_strlen(path));
			if (!path)
				ft_error("Substr failed\n");
			return (path);
		}
	}
	return (NULL);
}

char	**get_paths(t_data *data)
{
	char	*str;
	char	**paths;

	str = get_line(data);
	paths = ft_split(str, ':');
	free(str);
	if (!paths)
		ft_error("Split failed\n");
	return (paths);
}
