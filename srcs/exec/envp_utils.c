/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:14 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 14:35:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*found_value_with_key(t_envp *envp, char *key, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp(envp[i].key, key) == 0)
			return (envp[i].value);
		i++;
	}
	return (NULL);
}

int	found_index_with_key(t_envp *envp, char *key, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp(envp[i].key, key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	update_value_with_key(t_envp *envp_s, int *size, char *key, char *val)
{
	int	index;

	index = found_index_with_key(envp_s, key, *size);
	if (index == -1)
		return (EXIT_SUCCESS);
	free(envp_s[index].value);
	envp_s[index].value = ft_strdup(val);
	if (!envp_s[index].value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	add_key_value(t_envp **envp_s, int *size, char *key, char *value)
{
	t_envp	*new_envp;
	t_envp	new_key_value;

	new_envp = (t_envp *)ft_calloc(sizeof(t_envp), *size + 1);
	if (!new_envp)
		return (EXIT_FAILURE);
	ft_memcpy(new_envp, *envp_s, sizeof(t_envp) * *size);
	new_key_value.key = ft_strdup(key);
	if (!new_key_value.key)
		return (EXIT_FAILURE);
	new_key_value.value = ft_strdup(value);
	if (!new_key_value.value)
		return (free(new_key_value.key), EXIT_FAILURE);
	new_envp[*size] = new_key_value;
	*size += 1;
	free(*envp_s);
	*envp_s = new_envp;
	return (EXIT_SUCCESS);
}

int	delete_key_value(t_envp **envp_s, int *size, char *key)
{
	t_envp	*new_envp;
	int		index;
	int		i;

	if (!found_value_with_key(*envp_s, key, *size) || key[0] == '?')
		return (EXIT_SUCCESS);
	index = found_index_with_key(*envp_s, key, *size);
	new_envp = (t_envp *)ft_calloc(sizeof(t_envp), *size - 1);
	if (!new_envp)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < *size)
	{
		if (i < index)
			new_envp[i] = (*envp_s)[i];
		else if (i > index)
			new_envp[i - 1] = (*envp_s)[i];
		else
			free_key_value((*envp_s)[i].key, (*envp_s)[i].value);
	}
	*size -= 1;
	free(*envp_s);
	*envp_s = new_envp;
	return (EXIT_SUCCESS);
}
