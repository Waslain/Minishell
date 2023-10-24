/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:59:07 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 20:59:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir_in(int token)
{
	if (token == REDIR_IN || token == APPEND_IN)
		return (true);
	return (false);
}

bool	is_redir_out(int token)
{
	if (token == REDIR_OUT || token == APPEND_OUT)
		return (true);
	return (false);
}

bool	is_file(int token)
{
	if (token == FILES_IN || token == HEREDOC || token == FILES_OUT)
		return (true);
	return (false);
}
