/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_tab_exec(t_cmd_tab *cmd_tab, t_lexer *lexer)
{
	char	*tmp;

	if (cmd_tab->cmd == NULL)
		cmd_tab->cmd = ft_strdup(lexer->str);
	else
	{
		tmp = cmd_tab->cmd;
		cmd_tab->cmd = ft_strjoin(cmd_tab->cmd, " ");
		free(tmp);
		tmp = cmd_tab->cmd;
		cmd_tab->cmd = ft_strjoin(cmd_tab->cmd, lexer->str);
		free(tmp);
	}
}

t_lexer	*parse_cmd_tab(t_cmd_tab *cmd_tab, t_lexer *lexer)
{
	while (lexer != NULL && lexer->type != PIPE)
	{
		if (lexer->type == FILES_IN)
			open_infile(cmd_tab, lexer);
		if (lexer->type == FILES_OUT)
			open_outfile(cmd_tab, lexer);
		if (lexer->type == CMD || lexer->type == ARGS)
		{
			parse_cmd_tab_exec(cmd_tab, lexer);
		}
		if (lexer->next != NULL)
			lexer = lexer->next;
		else
			return (lexer);
	}
	if (lexer->next != NULL)
		return (lexer->next);
	else
		return (lexer);
}
