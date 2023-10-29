/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/29 13:45:14 by obouhlel         ###   ########.fr       */
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
		ft_putendl_fd("Quit", STDERR);
		*status = 131;
	}
}

static
void	mode_signal_bis(int mode)
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

void	mode_signal(int mode)
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
		mode_signal_bis(mode);
}
