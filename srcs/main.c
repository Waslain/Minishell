/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:22:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 15:11:11 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	g_signal = 0;
	printf("SIG : %d\n", g_signal);
	ft_bzero(&data, sizeof(t_data));
	if (get_envp(&data, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (argc == 1)
		minishell_loop(&data);
	else
	{
		printf("Minishell doesn't take arguments");
		return (free_array(data.envp), -1);
	}
}
