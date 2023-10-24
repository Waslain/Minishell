/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char *lex)
{
	if (ft_strcmp(lex, "<") == 0)
		return (1);
	else if (ft_strcmp(lex, ">") == 0)
		return (1);
	else if (ft_strcmp(lex, "<<") == 0)
		return (1);
	else if (ft_strcmp(lex, ">>") == 0)
		return (1);
	else
		return (0);
}
