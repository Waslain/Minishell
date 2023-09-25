#include "minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_command_not_found_error(char *cmd)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(": command not found\n");
}

void	print_no_such_file(char *cmd)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(": No such file or directory\n");
}
