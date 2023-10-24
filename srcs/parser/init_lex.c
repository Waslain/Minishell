/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char *lex)
{
	if (ft_strcmp(lex, ">>") == 0)
		return (APPEND_OUT);
	else if (ft_strcmp(lex, "<<") == 0)
		return (APPEND_IN);
	else if (ft_strcmp(lex, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(lex, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(lex, "|") == 0)
		return (PIPE);
	else
		return (-1);
}

void	free_lex(t_lexer *lexer)
{
	t_lexer	*aux;

	while (lexer != NULL)
	{
		aux = lexer;
		lexer = lexer->next;
		free(aux);
	}
	lexer = NULL;
}

void	add_lex_end(t_lexer *lexer, char *str, int type)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		ft_error("minishell: lexer malloc failed");
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	while (lexer->next != NULL)
	{
		lexer = lexer->next;
	}
	lexer->next = new_node;
}

void	set_lexer_token(t_lexer *lexer)
{
	int		first;
	t_lexer	*prev;

	prev = NULL;
	first = 1;
	while (lexer != NULL)
	{
		if (first == 0 && lexer->type == -1)
			lexer->type = ARGS;
		else if (lexer->type == PIPE)
			first = 1;
		else if (prev && prev->type == REDIR_IN)
			lexer->type = FILES_IN;
		else if (prev && prev->type == REDIR_OUT)
			lexer->type = FILES_OUT;
		else if (prev && prev->type == APPEND_IN)
			lexer->type = HEREDOC;
		else if (first == 1 && is_token(lexer->str) == -1)
		{
			lexer->type = CMD;
			first = 0;
		}
		prev = lexer;
		lexer = lexer->next;
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
// 		else if (lexer->type == HEREDOC)
// 			printf("lex[%i]=[%s]-[HEREDOC]\n", i++, lexer->str);
// 		// printf("lex[%i]=[%s]-[%d]\n", i++, lexer->str, lexer->type);
// 		if (!lexer->next)
// 			break;
// 		lexer = lexer->next;
// 	}
// }

t_lexer	*init_lex(char **lex)
{
	t_lexer	*lexer;
	int		i;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		ft_error("minishell: lexer malloc failed");
	lexer->str = lex[0];
	lexer->type = is_token(lex[0]);
	lexer->next = NULL;
	i = 1;
	while (lex[i])
	{
		add_lex_end(lexer, lex[i], is_token(lex[i]));
		i++;
	}
	set_lexer_token(lexer);
	// print_lexlst(lexer);
	return (lexer);
}
