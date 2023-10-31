/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/31 18:23:04 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_parser(t_data *data)
{
	if (init_cmds(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_redir(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_redir_struct(data);
	return (EXIT_SUCCESS);
}
