/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/27 14:23:28 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	update_status_with_signal(int *status)
{
	if (*status == 2)
	{
		ft_putchar_fd('\n', STDERR);
		*status = 130;
	}
	else if (*status == 3)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR);
		*status = 131;
	}
}

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
	printf("Quit (core dumped)");
}

void	handler_end_spe(int signal1)
{
	if (signal1 == SIGINT)
	{
		rl_done = 1;
		g_signal = 1;
		write(1, "\n", 1);
		printf(BCYN"Minishell $> "CRESET);
	}
	else
		return ;
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
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
			unblock_signal(SIGINT);
		}
		else
			g_signal = 0;
	}
	else
		return ;
}

void	create_siga2(int mode)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	if (mode == S_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == S_HEREDOC)
	{
		act.sa_handler = &handler_end_spe;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	create_siga(int mode)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	if (mode == S_MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
		act.sa_handler = &handler_end;
		act.sa_flags = 0;
		sigaction(SIGINT, &act, NULL);
	}
	if (mode == S_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
		create_siga2(mode);
	return (0);
}
