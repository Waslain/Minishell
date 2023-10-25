/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:06:00 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 09:41:48 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	count_nb_files_for_cmd(t_data *data, t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer && i < data->parser.size_redir)
	{
		if (is_redir_in(lexer->type))
			data->parser.redir[i].nb_files++;
		else if (is_redir_out(lexer->type))
			data->parser.redir[i].nb_files++;
		else if (lexer->type == PIPE)
			i++;
		lexer = lexer->next;
	}
}

static
int	calloc_all_struct_files(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->parser.size_redir)
	{
		data->parser.redir[i].files = ft_calloc(data->parser.redir[i].nb_files, \
			sizeof(t_file));
		if (!data->parser.redir[i].files)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static
void	init_files_struct(t_data *data, t_lexer *lexer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lexer)
	{
		if (is_file(lexer->type) && j < data->parser.redir[i].nb_files)
		{
			data->parser.redir[i].files[j].name_file = lexer->str;
			data->parser.redir[i].files[j].type = lexer->type;
			j++;
		}
		else if (lexer->type == PIPE)
		{
			i++;
			j = 0;
		}
		lexer = lexer->next;
	}
}

int	init_redir(t_data *data)
{
	if (data->nb_cmd >= 0 && data->nb_redir == 0)
		return (EXIT_SUCCESS);
	else if (data->nb_cmd == 0 && data->nb_redir > 0)
		data->parser.size_redir = 1 + data->nb_pipe;
	else
		data->parser.size_redir = data->nb_cmd;
	data->parser.redir = ft_calloc(data->parser.size_redir, sizeof(t_redir));
	if (!data->parser.redir)
		return (EXIT_FAILURE);
	count_nb_files_for_cmd(data, data->lexer);
	if (calloc_all_struct_files(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_files_struct(data, data->lexer);
	return (EXIT_SUCCESS);
}
