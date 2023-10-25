/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/25 10:13:12 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	print_cmds_struct(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmd)
	{
		j = 0;
		while (data->parser.cmds[i].cmd[j])
		{
			printf("cmd[%d][%d] = %s\n", i, j, data->parser.cmds[i].cmd[j]);
			j++;
		}
		i++;
	}
}

static
void	print_redir_struct(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->parser.size_redir)
	{
		j = 0;
		while (j < data->parser.redir[i].nb_files)
		{
			printf("redir[%d][%d] = %s\n", i, j, \
				data->parser.redir[i].files[j].name_file);
			j++;
		}
		i++;
	}
}

int	main_parser(t_data *data)
{
	if (init_cmds(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_redir(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_cmds_struct(data);
	print_redir_struct(data);
	return (EXIT_SUCCESS);
}
