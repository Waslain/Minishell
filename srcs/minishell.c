/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 21:12:07 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	count_type_token(t_lexer *lexer, int type)
{
	int	nb;

	nb = 0;
	while (lexer)
	{
		if (lexer->type == type)
			nb++;
		lexer = lexer->next;
	}
	return (nb);
}

static
int	count_nb_redir(t_lexer *lexer)
{
	int	nb_redir;

	nb_redir = 0;
	while (lexer)
	{
		if (lexer->type == REDIR_IN || lexer->type == REDIR_OUT
			|| lexer->type == APPEND_IN || lexer->type == APPEND_OUT)
			nb_redir++;
		lexer = lexer->next;
	}
	return (nb_redir);
}

static
int	check_cmd(char *cmd)
{
	if (cmd == NULL)
	{
		write(1, "exit\n", 5);
		return (EXIT_MINISHELL);
	}
	if (ft_strcmp(cmd, "\0") == 0)
		return (EMPTY_COMMANDE);
	add_history(cmd);
	return (NO_ERROR);
}

static
int	minishell(t_data *data)
{
	char	*ret;
	char	**lex;
	char	**tmp;

	tmp = data->envp;
	ft_bzero(data, sizeof(t_data));
	data->envp = tmp;
	ret = readline(BCYN"Minishell $> "CRESET);
	if (check_cmd(ret) == EXIT_MINISHELL)
		return (free(ret), EXIT_MINISHELL);
	else if (check_cmd(ret) == EMPTY_COMMANDE)
		return (free(ret), EMPTY_COMMANDE);
	lex = clear_lex(data, ret);
	data->lexer = init_lex(lex);
	if (!data->lexer)
		return (EXIT_MINISHELL);
	print_lexlst(data->lexer);
	data->nb_cmd = count_type_token(data->lexer, CMD);
	data->nb_pipe = count_type_token(data->lexer, PIPE);
	data->nb_redir = count_nb_redir(data->lexer);
	if (main_parser(data) == EXIT_FAILURE)
		return (EXIT_MINISHELL);
	// if (main_exec(data) == EXIT_FAILURE)
	// 	return (EXIT_MINISHELL);
	free_parser(&data->parser, data->nb_cmd);
	free_lex(data->lexer);
	free_lexer(lex);
	free(ret);
	return (0);
}

int	minishell_loop(t_data *data)
{
	init_signal();
	while (1)
	{
		if (minishell(data) == 2)
			return (ft_free(data->envp), 1);
	}
	rl_clear_history();
	ft_free(data->envp);
	return (0);
}
