/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 20:51:09 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser(t_parser *parser, int nb_cmd)
{
	int	i;

	if (parser->cmds)
	{
		i = 0;
		while (i < nb_cmd)
		{
			free(parser->cmds[i].cmd);
			i++;
		}
		free(parser->cmds);
	}
	if (parser->redir)
	{
		i = 0;
		while (i < parser->size_redir)
		{
			free(parser->redir[i].files);
			i++;
		}
		free(parser->redir);
	}
}

static
void	print_cmds_struct(t_data *data)
{
	int i;
	int j;

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
	int i;
	int j;

	i = 0;
	while (i < data->parser.size_redir)
	{
		j = 0;
		while (j < data->parser.redir[i].nb_files)
		{
			printf("redir[%d][%d] = %s\n", i, j, data->parser.redir[i].files[j].name_file);
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
