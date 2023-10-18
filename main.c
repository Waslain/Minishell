#include "minishell.h"

int	g_error;

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

void	execsimplecommand(t_data *data)
{
	char	**paths;
	char	**cmd;
	char	*bin;

	cmd = ft_split(data->cmd, ' ');
	paths = get_paths(data);
	bin = get_bin(cmd[0], paths);
	execve(bin, cmd, data->envp);
	freeall(paths, cmd, bin);
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

int	minishell(t_data *data)
{
	char	*ret;
	char	**lex;

	ret = readline(BCYN"Minishell $> "CRESET);
	// printf("read line -> %s\n", ret);
	if (check_cmd(ret) == 2)
		return (free(ret), 2);
	else if (check_cmd(ret) == 1)
		return (free(ret), 1);
	data->cmd = ret;
	data->nb_pipe = nofpipes(ret);
	data->nb_cmd = data->nb_pipe + 1;
	lex = lexer(data->cmd);
	if (data->nb_cmd == 1)
		exec_no_pipe(data, lex);
	// else
	// 	exec_pipe();
	// print_lexer(lex);
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
			return(1);
		// minishell(data);
	}
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	data = get_envp(envp);
	if (argc == 1)
		minishell_loop(&data);
	else
	{
		printf("Minishell doesn't take arguments");
		return (-1);
	}
}