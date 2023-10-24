/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
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
		return (2);
	}
	if (ft_strcmp(cmd, "\0") == 0)
		return (1);
	add_history(cmd);
	return (0);
}

// printf("read line -> %s\n", ret);
// print_lexer(lex);

int	minishell(t_data *data)
{
	char	*ret;
	char	**lex;

	ret = readline(BCYN"Minishell $> "CRESET);
	if (check_cmd(ret) == 2)
		return (free(ret), 2);
	else if (check_cmd(ret) == 1)
		return (free(ret), 1);
	data->cmd = ret;
	data->nb_pipe = nofpipes(ret);
	data->nb_cmd = data->nb_pipe + 1;
	lex = clear_lex(data, data->cmd);
	if (data->nb_cmd == 1)
		exec_no_pipe(data, lex);
	else
		exec_pipe(data, lex, data->nb_pipe);
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
