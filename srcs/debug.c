/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:45:30 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 09:43:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*found_token(int token)
{
	if (token == FILES_IN)
		return ("FILES_IN");
	else if (token == FILES_OUT)
		return ("FILES_OUT");
	else if (token == FILES_OUT_APPEND)
		return ("FILES_OUT_APPEND");
	else if (token == REDIR_IN)
		return ("REDIR_IN");
	else if (token == REDIR_OUT)
		return ("REDIR_OUT");
	else if (token == APPEND_IN)
		return ("APPEND_IN");
	else if (token == APPEND_OUT)
		return ("APPEND_OUT");
	else if (token == HEREDOC)
		return ("HEREDOC");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == CMD)
		return ("CMD");
	else if (token == ARGS)
		return ("ARGS");
	return ("NOT FOUND");
}

void	print_lexlst(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		printf("lex[%i]=[%s]-[%s]\n", i, found_token(lexer->type), lexer->str);
		i++;
		lexer = lexer->next;
	}
}
