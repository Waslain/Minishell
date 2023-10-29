/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:19:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 13:10:44 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_signal;

void	block_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

void	unblock_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
}

void	handler_quit(int signal)
{
	if (signal != SIGQUIT)
	{
		block_signal(SIGQUIT);
		return ;
	}
	ft_putstr_fd("Quit", STDERR);
}

void	handler_end_spe(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR);
		ctrl_c_heredoc((t_heredoc){NULL, NULL, 0}, NULL, DESTROY);
		exit(130);
	}
}

void	handler_end(int signal)
{
	if (signal == SIGINT)
	{
		if (g_signal == 0 || g_signal == 2)
		{
			block_signal(SIGINT);
			g_signal = 2;
			rl_on_new_line();
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
			unblock_signal(SIGINT);
		}
		else
			g_signal = 0;
	}
}
