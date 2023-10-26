/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:17:56 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 09:57:41 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	calculate_size_array_cmd(t_lexer *lexer)
{
	int	size_cmd;

	size_cmd = 0;
	while (lexer)
	{
		if (lexer->type == CMD)
		{
			size_cmd = 1;
			lexer = lexer->next;
			break ;
		}
		lexer = lexer->next;
	}
	if (!lexer && size_cmd == 0)
		return (size_cmd);
	while (lexer && (lexer)->type != PIPE)
	{
		if ((lexer)->type == ARGS)
			size_cmd++;
		lexer = lexer->next;
	}
	return (size_cmd);
}

static
int	create_array_cmd(char ***cmds, t_lexer **lexer_copy)
{
	int		size_cmd;
	int		i;

	size_cmd = calculate_size_array_cmd(*lexer_copy);
	(*cmds) = ft_calloc(size_cmd + 1, sizeof(char *));
	if (!(*cmds))
		return (EXIT_FAILURE);
	while ((*lexer_copy))
	{
		if ((*lexer_copy)->type == CMD)
		{
			(*cmds)[0] = (*lexer_copy)->str;
			(*lexer_copy) = (*lexer_copy)->next;
			break ;
		}
		(*lexer_copy) = (*lexer_copy)->next;
	}
	i = 1;
	while ((*lexer_copy) && (*lexer_copy)->type != PIPE)
	{
		if ((*lexer_copy)->type == ARGS)
			(*cmds)[i++] = (*lexer_copy)->str;
		(*lexer_copy) = (*lexer_copy)->next;
	}
	return (EXIT_SUCCESS);
}

int	init_cmds(t_data *data)
{
	int		i;
	int		ret;
	t_lexer	*lexer_copy;

	lexer_copy = data->lexer;
	data->parser.cmds = ft_calloc(data->nb_cmd, sizeof(t_cmds));
	if (!data->parser.cmds)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_cmd)
	{
		ret = create_array_cmd(&data->parser.cmds[i].cmd, &lexer_copy);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
