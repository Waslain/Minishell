#include "minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_data *data, char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		builtin_env(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit();
	return (1);
}
