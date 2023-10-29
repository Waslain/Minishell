/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:22:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 14:30:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static
void	check_is_terminal(void)
{
	struct termios	termios;

	if (tcgetattr(STDIN_FILENO, &termios) == -1)
	{
		perror("minishell: tcgetattr");
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(STDOUT_FILENO, &termios) == -1)
	{
		perror("minishell: tcgetattr");
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(STDERR_FILENO, &termios) == -1)
	{
		perror("minishell: tcgetattr");
		exit(EXIT_FAILURE);
	}
	(void)termios;
}

int	main(int argc, char **argv, char **envp)
{
	t_data			data;

	(void)argv;
	check_is_terminal();
	if (argc != 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR);
		return (EXIT_FAILURE);
	}
	mode_signal(S_MAIN);
	ft_bzero(&data, sizeof(t_data));
	if (get_envp(&data, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	minishell_loop(&data);
	return (EXIT_SUCCESS);
}
