/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:57:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/31 15:42:46 by obouhlel         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

static
int	check_cmd_and_signal(char *cmd, t_data *data, int *exit_code)
{
	if (g_signal == 2)
		*exit_code = 130;
	if (cmd == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT);
		free(cmd);
		destroy_data(data, DESTROY_ENV);
		rl_clear_history();
		exit(*exit_code);
	}
	if (ft_strcmp(cmd, "\0") == 0)
		return (EMPTY_COMMANDE);
	if (all_is_white_space(cmd))
		return (EMPTY_COMMANDE);
	if (g_signal == 2)
	{
		if (update_exit_code_signal(data, 130))
			return (EXIT_MINISHELL);
	}
	add_history(cmd);
	mode_signal(S_PARENT);
	return (NO_ERROR);
}

static
int	minishell(t_data *data, char *rl, int *exit_code)
{
	char	**lex;

	lex = clear_lex(data, rl);
	if (!lex)
		return (EMPTY_COMMANDE);
	data->lexer = init_lex(data, lex);
	if (!data->lexer)
		return (free_array(lex), malloc_error(data), EXIT_FAILURE);
	data->to_free = lex;
	data->nb_cmd = count_type_token(data->lexer, CMD);
	data->nb_pipe = count_type_token(data->lexer, PIPE);
	data->nb_redir = count_nb_redir(data->lexer);
	if (heredoc(data) == EXIT_FAILURE)
		return (malloc_error(data), EXIT_MINISHELL);
	if (main_parser(data) == EXIT_FAILURE)
		return (malloc_error(data), EXIT_MINISHELL);
	if (main_exec(data) == EXIT_FAILURE)
		return (malloc_error(data), EXIT_MINISHELL);
	unlink_all_heredoc(data);
	*exit_code = data->exec.status;
	free_lexer(lex);
	return (destroy_data(data, DONT_DESTROY_ENV), 0);
}

int	minishell_loop(t_data *data)
{
	static int	exit_code = 0;
	char		*ret;
	int			return_check;

	while (1)
	{
		g_signal = 0;
		mode_signal(S_MAIN);
		ret = readline(BCYN"Minishell $> "CRESET);
		return_check = check_cmd_and_signal(ret, data, &exit_code);
		if (return_check == EMPTY_COMMANDE)
		{
			free(ret);
			continue ;
		}
		mode_signal(S_PARENT);
		if (minishell(data, ret, &exit_code) == EXIT_MINISHELL)
			return (destroy_data(data, DESTROY_ENV), rl_clear_history(), 1);
	}
	return (EXIT_SUCCESS);
}
