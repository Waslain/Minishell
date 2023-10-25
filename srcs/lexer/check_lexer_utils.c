/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:55:57 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/25 10:27:08 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

// NEED TO PATCH THIS FUNCTION
void	print_delimiter_error(char *delimiter)
{
	print_error("minishell: syntax error near unexpected token '");
	print_error(delimiter);
	print_error("'\n");
	exit(0);
}
