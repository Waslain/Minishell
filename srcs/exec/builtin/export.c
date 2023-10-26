/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:13:13 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 14:37:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	add_envp_bis(char *str, t_data *d, char *key)
{
	char	*val;

	val = found_value_with_key(d->exec.envp_s, key, d->exec.size);
	if (!val)
	{
		val = get_value(str);
		if (!val)
			return (ft_free((void **)key), malloc_error(d));
		if (add_key_value(&d->exec.envp_s, &d->exec.size, key, val))
			return (free_key_value(key, val), malloc_error(d));
		return (free_key_value(key, val));
	}
	else
	{
		val = get_value(str);
		if (!val)
			return (ft_free((void **)key), malloc_error(d));
		if (update_value_with_key(d->exec.envp_s, &d->exec.size, key, val))
			return (ft_free((void **)key), malloc_error(d));
		return (free_key_value(key, val));
	}
}

static
void	add_envp(char *str, t_data *d, bool equal_exist)
{
	char	*key;

	key = get_key(str);
	if (!key)
		return (ft_free((void **)key), malloc_error(d));
	if (!equal_exist)
	{
		if (add_key_value(&d->exec.envp_s, &d->exec.size, key, ""))
			return (ft_free((void **)key), malloc_error(d));
	}
	add_envp_bis(str, d, key);
}

static
bool	check_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalphanum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static
void	print_export(t_data *data)
{
	int				i;
	const t_envp	*envp = data->exec.envp_s;

	i = 1;
	while (i < data->exec.size)
	{
		ft_putstr_fd("export ", STDOUT);
		ft_putstr_fd(envp[i].key, STDOUT);
		if (envp[i].value && envp[i].value[0] != '\0')
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(envp[i].value, STDOUT);
			ft_putstr_fd("\"", STDOUT);
		}
		ft_putstr_fd("\n", STDOUT);
		i++;
	}
}

int	export(t_data *data)
{
	const int	id = data->exec.id_child;
	const char	**cmds = (const char **)data->parser.cmds[id].cmd;
	int			i;
	bool		equal_exist;

	i = 1;
	if (!cmds[i])
		return (print_export(data), EXIT_SUCCESS);
	while (cmds[i])
	{
		equal_exist = false;
		if (ft_strchr(cmds[i], '=') != NULL)
			equal_exist = true;
		if (check_key((char *)cmds[i]))
			add_envp((char *)cmds[i], data, equal_exist);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR);
			ft_putstr_fd((char *)cmds[i], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
