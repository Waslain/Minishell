/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 13:11:22 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data, const int id)
{
	char	*pwd;
	int		ret;

	(void)id;
	(void)data;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (error_child(data, "pwd", strerror(errno), 1), EXIT_FAILURE);
	ret = ft_putendl_fd(pwd, STDOUT);
	if (ret == -1)
		return (error_child(data, "pwd", ERROR_WRITE, 1), EXIT_FAILURE);
	free(pwd);
	return (EXIT_SUCCESS);
}
