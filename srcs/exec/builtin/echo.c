/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 13:09:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	is_option(char *str, bool *endl)
{
	int	i;

	if (str[0] && str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	if (*endl == true)
		*endl = false;
	return (true);
}

static
void	insert_newline(bool endl, t_data *data)
{
	int	ret;

	if (endl)
	{
		ret = ft_putchar_fd('\n', STDOUT);
		if (ret == -1)
			return (error_child(data, "echo", ERROR_WRITE, 1));
	}
}

int	echo(t_data *data, const int id)
{
	const char	**cmd = (const char **)data->parser.cmds[id].cmd;
	bool		endl;
	int			i;
	int			ret;

	i = 1;
	endl = true;
	while (cmd[i] && is_option((char *)cmd[i], &endl))
		i++;
	while (cmd[i])
	{
		ret = ft_putstr_fd((char *)cmd[i], STDOUT);
		if (ret == -1)
			return (error_child(data, "echo", ERROR_WRITE, 1), EXIT_FAILURE);
		if (cmd[i + 1])
		{
			ret = ft_putstr_fd(" ", STDOUT);
			if (ret == -1)
				return (error_child(data, "echo", ERROR_WRITE, 1), 1);
		}
		i++;
	}
	insert_newline(endl, data);
	return (EXIT_SUCCESS);
}
