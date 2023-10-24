/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:23:06 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 21:23:09 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd_tab	*aux;

	while (cmd_tab != NULL)
	{
		aux = cmd_tab;
		if (cmd_tab->cmd != NULL)
			free(cmd_tab->cmd);
		cmd_tab = cmd_tab->next;
		free(aux);
	}
	cmd_tab = NULL;
}

t_cmd_tab	*add_cmd(t_cmd_tab *cmd_tab)
{
	t_cmd_tab	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd_tab));
	if (!new_cmd)
		ft_error("minishell: cmd_tab malloc failed");
	new_cmd->cmd = NULL;
	new_cmd->next = NULL;
	while (cmd_tab->next != NULL)
		cmd_tab = cmd_tab->next;
	cmd_tab->next = new_cmd;
	return (new_cmd);
}

t_cmd_tab	*init_cmd_tab(t_lexer *lexer, int nop)
{
	t_cmd_tab	*cmd_tab;
	t_cmd_tab	*addtab;

	cmd_tab = malloc(sizeof(t_cmd_tab));
	if (!cmd_tab)
		ft_error("minishell: cmd_tab malloc failed");
	cmd_tab->cmd = NULL;
	cmd_tab->next = NULL;
	lexer = parse_cmd_tab(cmd_tab, lexer);
	while (nop > 0)
	{
		addtab = add_cmd(cmd_tab);
		lexer = parse_cmd_tab(addtab, lexer);
		nop--;
	}
	return (cmd_tab);
}
