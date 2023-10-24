/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 18:37:08 by fduzant          ###   ########.fr       */
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
	return (lexer);
}
