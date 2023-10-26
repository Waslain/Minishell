/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:52:03 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 13:13:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	count_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	*get_key(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (ft_substr(str, 0, len));
}

char	*get_value(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (ft_substr(str, len + 1, ft_strlen(str) - len));
}

int	conv_env_to_struct(char **envp, t_envp **envp_s, int *size)
{
	int	i;

	*size = count_envp(envp);
	(*envp_s) = (t_envp *)ft_calloc(sizeof(t_envp), *size);
	if (!(*envp_s))
		return (EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		(*envp_s)[i].key = get_key(envp[i]);
		(*envp_s)[i].value = get_value(envp[i]);
		if (!(*envp_s)[i].key || !(*envp_s)[i].value)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	conv_env_struct_to_env(char ***envp, t_envp *envp_s, int size)
{
	int		i;
	char	*tmp;

	free_array(*envp);
	*envp = NULL;
	(*envp) = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!(*envp))
		return (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		tmp = ft_strjoin(envp_s[i].key, "=");
		if (!tmp)
			return (EXIT_FAILURE);
		(*envp)[i] = ft_strjoin(tmp, envp_s[i].value);
		if (!(*envp)[i])
			return (free(tmp), EXIT_FAILURE);
		ft_free((void **)&tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
