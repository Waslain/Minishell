#include "minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	freeall(char **cmd, char **paths, char *bin)
{
	ft_free(cmd);
	ft_free(paths);
	free(bin);
}

t_data	get_args(int argc, char **argv)
{
	t_data	tmp;

	tmp.argc = argc;
	tmp.argv = argv;
	return (tmp);
}

t_data	get_envp(char **envp)
{
	t_data	tmp;

	tmp.envp = envp;
	return (tmp);
}

void	ft_error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
