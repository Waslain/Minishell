/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:33:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 12:14:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_child(t_data *data, const char *arg, const char *msg, int val)
{
	if (arg && !msg)
	{
		ft_putstr_fd("minishell: ", STDERR);
		perror(arg);
	}
	else if (arg && msg)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd((char *)arg, STDERR);
		ft_putendl_fd((char *)msg, STDERR);
	}
	destroy_data(data, DESTROY_ENV);
	if (val == -1)
		exit(errno);
	else
		exit(val);
}
