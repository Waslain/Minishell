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

void	minishell(t_data *data)
{
	char	*ret;
	char	**lex;

	ret = readline(BCYN"Minishell $> "CRESET);
	data->cmd = ret;
	data->nb_pipe = nofpipes(ret);
	data->nb_cmd = data->nb_pipe + 1;
	// if (data->nb_cmd == 1)
	// 	execsimplecommand(data);
	lex = lexer(data->cmd);
	print_lexer(lex);
	free_lexer(lex);
	free(ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	data = get_envp(envp);
	if (argc == 1)
		minishell(&data);
	else
	{
		printf("Minishell doesn't take arguments");
		return (-1);
	}
}