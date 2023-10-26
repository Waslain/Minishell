/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:17:02 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 10:23:50 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(char *name, int type)
{
	if (type == FILES_IN || type == HEREDOC)
		return (open(name, O_RDONLY));
	else if (type == FILES_OUT)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == FILES_OUT_APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (NO_FILE);
}

int	open_infile(t_file *file, int size, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = NO_FILE;
	while (i < size)
	{
		if (fd != NO_FILE && is_infile(file[i].type))
			ft_close(&fd);
		if (is_infile(file[i].type))
		{
			fd = ft_open(file[i].name_file, file[i].type);
			if (fd == ERROR_FILE)
				return (error_child(data, file[i].name_file, NULL), ERROR_FILE);
		}
		i++;
	}
	return (fd);
}

int	open_outfile(t_file *file, int size, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = NO_FILE;
	while (i < size)
	{
		if (fd != NO_FILE && is_outfile(file[i].type))
			ft_close(&fd);
		if (is_outfile(file[i].type))
		{
			fd = ft_open(file[i].name_file, file[i].type);
			if (fd == ERROR_FILE)
				return (error_child(data, file[i].name_file, NULL), ERROR_FILE);
		}
		i++;
	}
	return (fd);
}
