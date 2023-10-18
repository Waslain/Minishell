#include "minishell.h"

int	builtin_pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
	{
		printf("Error cannot get repository\n");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}
