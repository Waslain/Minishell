#include "minishell.h"

void	builtin_exit()
{
	write(1, "exit\n", 5);
	exit(0);
}
