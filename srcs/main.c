/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:22:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 21:22:17 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	if (get_envp(&data, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (argc == 1)
		minishell_loop(&data);
	else
	{
		printf("Minishell doesn't take arguments");
		return (ft_free(data.envp), -1);
	}
}
