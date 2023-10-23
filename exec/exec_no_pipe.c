/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_no_pipe(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		init_signal2();
		execsimplecommand(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		init_signal();
	}
	wait(&pid);
}

void	exec_no_pipe(t_data *data, char **lex)
{
	if (is_builtin(lex[0]))
	{
		exec_builtin(data, lex[0], lex);
		return ;
	}
	fork_no_pipe(data);
}
