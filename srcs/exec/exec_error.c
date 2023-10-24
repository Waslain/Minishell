/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_command_not_found_error(char *cmd)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(": command not found\n");
}

void	print_no_such_file(char *cmd)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(": No such file or directory\n");
}
