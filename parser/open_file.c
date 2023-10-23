/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd_open(int fd)
{
	if (fd > 2)
		close(fd);
}

void	open_infile(t_cmd_tab *cmd_tab, t_lexer *lexer)
{
	check_fd_open(cmd_tab->in_fd);
	cmd_tab->in_fd = open(lexer->str, O_RDONLY);
	if (cmd_tab->in_fd == -1)
		ft_error("Minishell: openning infile failed");
}

void	open_outfile(t_cmd_tab *cmd_tab, t_lexer *lexer)
{
	check_fd_open(cmd_tab->out_fd);
	cmd_tab->out_fd = open(lexer->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_tab->out_fd == -1)
		ft_error("Minishell: openning outfile failed");
}
