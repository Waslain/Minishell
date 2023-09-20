#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	nofpipes(char **cmd)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	x = 0;
	while (cmd[i])
	{
		y = 0;
		while (cmd[i][y])
		{
			printf("%c\n", cmd[i][y]);
			if (cmd[i][y] == '|')
				x++;
			y++;
		}
		i++;

	}
	return (x);
}

void	execsimplecommand(t_data *data)
{
	char	**paths;
	char	**cmd;
	char	*bin;

	cmd = data->argv;
	paths = get_paths(data);
	bin = get_bin(cmd[0], paths);
	execve(bin, cmd, data->envp);
	freeall(paths, cmd, bin);
}

void	minishell(t_data *data)
{
	char	*ret_line;

	ret_line = readline(BCYN"Minishell $> "CRESET);
	data->argv = ft_split(ret_line, ' ');
	printf("Resultat split : %s\n", data->argv[0]);
	data->nb_pipe = nofpipes(data->argv);
	data->nb_cmd = data->nb_pipe + 1;
	if (data->nb_cmd == 1)
		execsimplecommand(data);
	// newpipe(data);
	free(ret_line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data = get_envp(envp);
	if (argc == 1)
		minishell(&data);
	else
		ft_error("Minishell doesn't take arguments");
	// printf("Number of pipes%d\n", nofpipes(argv));
	if (data.nb_pipe > 0)
		close_pipe(&data);
}