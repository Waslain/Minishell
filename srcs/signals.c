/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/26 11:56:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signal(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, &handler_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal2(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
