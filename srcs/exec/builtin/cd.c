/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:45:41 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 09:22:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	update_pwd(char **pwd, t_exec *exec)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_FAILURE);
	exec->to_free = path;
	if (ft_strncmp(*pwd, ".", ft_strlen(*pwd)) == 0)
	{
		*pwd = path;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(*pwd, "..", ft_strlen(*pwd)) == 0)
	{
		*pwd = ft_strrchr(path, '/');
		if (!(*pwd))
		{
			*pwd = path;
			return (EXIT_SUCCESS);
		}
	}
	*pwd = path;
	return (EXIT_SUCCESS);
}

static
int	update_pwd_oldpwd(char *new_pwd, t_exec *exec)
{
	char	*oldpwd;
	char	*check_oldpwd;

	if (update_pwd(&new_pwd, exec))
		return (EXIT_FAILURE);
	oldpwd = found_value_with_key(exec->envp_s, "PWD", exec->size);
	check_oldpwd = found_value_with_key(exec->envp_s, "OLDPWD",
			exec->size);
	if (oldpwd)
	{
		if (!check_oldpwd)
		{
			if (add_key_value(&exec->envp_s, &exec->size, \
											"OLDPWD", oldpwd))
				return (EXIT_FAILURE);
		}
		else if (update_value_with_key(exec->envp_s, &exec->size, \
										"OLDPWD", oldpwd))
			return (EXIT_FAILURE);
		if (update_value_with_key(exec->envp_s, &exec->size, "PWD", new_pwd))
			return (EXIT_FAILURE);
	}
	else if (add_key_value(&exec->envp_s, &exec->size, "PWD", new_pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static
int	go_to_home(t_data *data)
{
	char	*home;
	int		ret;

	home = found_value_with_key(data->exec.envp_s, "HOME", data->exec.size);
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", STDERR);
		return (EXIT_FAILURE);
	}
	ret = chdir(home);
	if (ret == -1)
	{
		ft_putstr_fd("cd: ", STDERR);
		ft_putstr_fd(home, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		return (EXIT_FAILURE);
	}
	if (update_pwd_oldpwd(home, &data->exec) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static
int	go_to_path(t_data *data, char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		ft_putstr_fd("cd: ", STDERR);
		ft_putstr_fd(path, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		return (EXIT_FAILURE);
	}
	if (update_pwd_oldpwd(path, &data->exec))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cd(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	**cmds = (const char **)data->parser.cmds[id].cmd;
	const int	nb_args = count_args(cmds);
	int			ret;

	ret = 0;
	if (nb_args > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR);
		return (EXIT_FAILURE);
	}
	if (nb_args == 1)
	{
		ret = go_to_home(data);
		if (ret)
			return (ret);
	}
	else
	{
		ret = go_to_path(data, (char *)cmds[1]);
		if (ret)
			return (ret);
	}
	return (EXIT_SUCCESS);
}
