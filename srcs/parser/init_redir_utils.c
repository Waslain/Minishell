/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:59:07 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 10:00:25 by obouhlel         ###   ########.fr       */
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

bool	is_infile(int token)
{
	if (token == FILES_IN || token == HEREDOC)
		return (true);
	return (false);
}

bool	is_outfile(int token)
{
	if (token == FILES_OUT || token == FILES_OUT_APPEND)
		return (true);
	return (false);
}

bool	is_file(int token)
{
	if (is_infile(token) || is_outfile(token))
		return (true);
	return (false);
}
