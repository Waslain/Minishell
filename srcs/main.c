/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 12:46:43 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nofpipes(char *cmd)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			x++;
		i++;
	}
	return (x);
}

int	check_cmd(char *cmd)
{
	if (cmd == NULL)
	{
		write(1, "exit\n", 5);
		return (EXIT_MINISHELL);
	}
	if (ft_strcmp(cmd, "\0") == 0)
		return (1);
	add_history(cmd);
	return (0);
}

int	minishell(t_data *data)
{
	char	*ret;
	char	**lex;

	ret = readline(BCYN"Minishell $> "CRESET);
	if (check_cmd(ret) == EXIT_MINISHELL)
		return (free(ret), EXIT_MINISHELL);
	else if (check_cmd(ret) == EMPTY_COMMANDE)
		return (free(ret), EMPTY_COMMANDE);
	data->cmd = ret;
	data->nb_pipe = nofpipes(ret);
	data->nb_cmd = data->nb_pipe + 1;
	lex = clear_lex(data, data->cmd);
	data->lexer = init_lex(lex);
	if (!data->lexer)
		return (EXIT_MINISHELL);
	print_lexlst(data->lexer);
	if (main_exec(data) == EXIT_FAILURE)
		return (EXIT_MINISHELL);
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
			return (ft_free(data->envp), free(data), 1);
	}
	rl_clear_history();
	ft_free(data->envp);
	free(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = malloc(sizeof(t_data));
	data = get_envp(data, envp);
	if (argc == 1)
		minishell_loop(data);
	else
	{
		printf("Minishell doesn't take arguments");
		return (ft_free(data->envp), free(data), -1);
	}
}
