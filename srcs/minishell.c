/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:57:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 15:17:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_signal;

static
int	update_exit_code_signal(t_data *data, int value)
{
	char	*exit_code;
	char	*tmp;

	exit_code = ft_itoa(value);
	if (!value)
		return (malloc_error(data), EXIT_FAILURE);
	tmp = ft_strjoin("?=", exit_code);
	if (!tmp)
		return (free(exit_code), malloc_error(data), EXIT_FAILURE);
	ft_free((void **)&data->envp[0]);
	free(exit_code);
	data->envp[0] = tmp;
	printf("data->envp[0] = %s\n", data->envp[0]);
	return (EXIT_SUCCESS);
}

static
int	check_cmd(char *cmd, t_data *data)
{
	printf("g_signal = %d\n", g_signal);
	if (cmd == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT);
		free(cmd);
		destroy_data(data, DESTROY_ENV);
		rl_clear_history();
		exit(0);
	}
	if (ft_strcmp(cmd, "\0") == 0)
		return (EMPTY_COMMANDE);
	add_history(cmd);
	mode_signal(S_PARENT);
	if (g_signal == 2)
	{
		if (update_exit_code_signal(data, 130))
			return (EXIT_MINISHELL);
	}
	return (NO_ERROR);
}

static
int	minishell(t_data *data, char *rl)
{
	char	**lex;

	lex = clear_lex(data, rl);
	if (!lex)
		return (EMPTY_COMMANDE);
	data->lexer = init_lex(data, lex);
	if (!data->lexer)
		return (free_array(lex), malloc_error(data), EXIT_FAILURE);
	print_lexlst(data->lexer);
	data->to_free = lex;
	data->nb_cmd = count_type_token(data->lexer, CMD);
	data->nb_pipe = count_type_token(data->lexer, PIPE);
	data->nb_redir = count_nb_redir(data->lexer);
	if (main_parser(data) == EXIT_FAILURE)
		return (EXIT_MINISHELL);
	// if (heredoc(data) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	if (main_exec(data) == EXIT_FAILURE)
		return (EXIT_MINISHELL);
	free_lexer(lex);
	return (destroy_data(data, DONT_DESTROY_ENV), 0);
}

int	minishell_loop(t_data *data)
{
	char	*ret;
	int		return_check;

	while (1)
	{
		g_signal = 0;
		mode_signal(S_MAIN);
		ret = readline(BCYN"Minishell $> "CRESET);
		return_check = check_cmd(ret, data);
		if (return_check == EMPTY_COMMANDE)
		{
			free(ret);
			continue ;
		}
		mode_signal(S_PARENT);
		if (minishell(data, ret) == EXIT_FAILURE)
			return (destroy_data(data, DESTROY_ENV), rl_clear_history(), 1);
	}
	return (EXIT_SUCCESS);
}
