/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/25 10:12:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
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

static
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

static
void	set_lexer_token(t_lexer *lexer, t_lexer *prev)
{
	int		first;

	first = 1;
	while (lexer != NULL)
	{
		if (lexer->type == PIPE)
			first = 1;
		else if (prev && prev->type == REDIR_IN)
			lexer->type = FILES_IN;
		else if (prev && prev->type == REDIR_OUT)
			lexer->type = FILES_OUT;
		else if (prev && prev->type == APPEND_IN)
			lexer->type = HEREDOC;
		else if (prev && prev->type == APPEND_OUT)
			lexer->type = FILES_OUT_APPEND;
		else if (first == 0 && lexer->type == -1)
			lexer->type = ARGS;
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
	t_lexer	*prev;

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
	prev = NULL;
	set_lexer_token(lexer, prev);
	return (lexer);
}
