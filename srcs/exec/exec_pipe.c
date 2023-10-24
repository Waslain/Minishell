/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all_cmd_tab(t_cmd_tab *cmd_tab)
{
	int	i;

	i = 1;
	while (cmd_tab != NULL)
	{
		printf("CMD[%d][%s]\n", i++, cmd_tab->cmd);
		cmd_tab = cmd_tab->next;
	}
}

// void	print_lexlst(t_lexer *lexer)
// {
// 	int	i;

// 	i = 0;
// 	while (lexer)
// 	{
// 		if (lexer->type == CMD)
// 			printf("lex[%i]=[%s]-[CMD]\n", i++, lexer->str);
// 		else if (lexer->type == ARGS)
// 			printf("lex[%i]=[%s]-[ARGS]\n", i++, lexer->str);
// 		else if (lexer->type == PIPE)
// 			printf("lex[%i]=[%s]-[PIPE]\n", i++, lexer->str);
// 		else if (lexer->type == FILES_IN)
// 			printf("lex[%i]=[%s]-[INFILE]\n", i++, lexer->str);
// 		else if (lexer->type == FILES_OUT)
// 			printf("lex[%i]=[%s]-[OUTFILE]\n", i++, lexer->str);
// 		else if (lexer->type == REDIR_IN)
// 			printf("lex[%i]=[%s]-[REDIR_IN]\n", i++, lexer->str);
// 		else if (lexer->type == REDIR_OUT)
// 			printf("lex[%i]=[%s]-[REDIR_OUT]\n", i++, lexer->str);
// 		else if (lexer->type == APPEND_IN)
// 			printf("lex[%i]=[%s]-[APPEND_IN]\n", i++, lexer->str);
// 		else if (lexer->type == APPEND_OUT)
// 			printf("lex[%i]=[%s]-[APPEND_OUT]\n", i++, lexer->str);
// 		// printf("lex[%i]=[%s]-[%d]\n", i++, lexer->str, lexer->type);
// 		if (!lexer->next)
// 			break;
// 		lexer = lexer->next;
// 	}
// }

void	exec_pipe(t_data *data, char **lex, int nop)
{
	t_lexer		*lexer;
	t_cmd_tab	*cmd_tab;
	int			pid;

	lexer = init_lex(lex);
	// print_lexlst(lexer);
	cmd_tab = init_cmd_tab(lexer, nop);
	// printf("IN_ID%d\n", cmd_tab->in_fd);
	print_all_cmd_tab(cmd_tab);
	/*
	EXEC ICIIIIIIIIIIIIIIIIIIIIIIII
	EXEC ICIIIIIIIIIIIIIIIIIIIIIIII
	EXEC ICIIIIIIIIIIIIIIIIIIIIIIII
	EXEC ICIIIIIIIIIIIIIIIIIIIIIIII
	EXEC ICIIIIIIIIIIIIIIIIIIIIIIII
	*/
	free_cmd_tab(cmd_tab);
	free_lex(lexer);
}
