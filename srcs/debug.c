/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:45:30 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 12:49:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexlst(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->type == CMD)
			printf("lex[%i]=[%s]-[CMD]\n", i++, lexer->str);
		else if (lexer->type == ARGS)
			printf("lex[%i]=[%s]-[ARGS]\n", i++, lexer->str);
		else if (lexer->type == PIPE)
			printf("lex[%i]=[%s]-[PIPE]\n", i++, lexer->str);
		else if (lexer->type == FILES_IN)
			printf("lex[%i]=[%s]-[INFILE]\n", i++, lexer->str);
		else if (lexer->type == FILES_OUT)
			printf("lex[%i]=[%s]-[OUTFILE]\n", i++, lexer->str);
		else if (lexer->type == REDIR_IN)
			printf("lex[%i]=[%s]-[REDIR_IN]\n", i++, lexer->str);
		else if (lexer->type == REDIR_OUT)
			printf("lex[%i]=[%s]-[REDIR_OUT]\n", i++, lexer->str);
		else if (lexer->type == APPEND_IN)
			printf("lex[%i]=[%s]-[APPEND_IN]\n", i++, lexer->str);
		else if (lexer->type == APPEND_OUT)
			printf("lex[%i]=[%s]-[APPEND_OUT]\n", i++, lexer->str);
		else if (lexer->type == HEREDOC)
			printf("lex[%i]=[%s]-[HEREDOC]\n", i++, lexer->str);
		lexer = lexer->next;
	}
}
