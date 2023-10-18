#include "minishell.h"

void	fork_no_pipe(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		init_signal2();
		execsimplecommand(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		init_signal();
	}
	wait(&pid);
}

void	exec_no_pipe(t_data *data, char **lex)
{
	if (is_builtin(lex[0]))
	{
		exec_builtin(data, lex[0]);
		return ;
	}
	fork_no_pipe(data);
}