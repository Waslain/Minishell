/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
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
		// check_fd_open(cmd_tab->in_fd);
		// check_fd_open(cmd_tab->out_fd);
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
	new_cmd->in_fd = -1;
	new_cmd->out_fd = -1;
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
	cmd_tab->in_fd = -1;
	cmd_tab->out_fd = -1;
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
