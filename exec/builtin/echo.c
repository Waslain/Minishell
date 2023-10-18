#include "minishell.h"

int	check_options(char **cmd, int i)
{
	int	x;

	x = 2;
	if (!cmd[i] || cmd[i][0] != '-' || cmd[i][1] != 'n')
		return (0);
	/*while (cmd[i] && cmd[i][x])
	{
		if (cmd[i][x] != 'n')
			return (0);
		x++;
	}*/
	return (1);
}

void	builtin_echo(t_data *data)
{
	char	**cmd;
	int	i;
	int	x;

	cmd = ft_split(data->cmd, ' ');
	i = 1;
	if (check_options(cmd, i) == 1)
		i++;
	while (cmd[i])
	{
		x = 0;
		while (cmd[i][x])
		{
			write(1, &cmd[i][x], 1);
			x++;
		}
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!check_options(cmd, 1) == 1)
		write(1, "\n", 1);
}
