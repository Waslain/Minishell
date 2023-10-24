/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all_cmd_tab(t_cmd_tab *cmd_tab)
{
	int	i;

	i = 1;
	while (cmd_tab != NULL)
	{
		printf("CMD[%d][%s]\n", i++, cmd_tab->cmd);
		cmd_tab = cmd_tab->next;
	}
}

void	child_process(t_cmd_tab *cmd_tab, t_data *data)
{
	pid_t	pid;
	int		fd[2];
	// char	**cmd;

	// cmd = ft_split(data->cmd, ' ');
	if (pipe(fd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (cmd_tab->out_fd != -1)
		{
			dup2(cmd_tab->out_fd, STDOUT_FILENO);
			close(cmd_tab->out_fd);
		}
		// if (is_builtin(cmd[0]))
		// {
		// 	exec_builtin(data, cmd[0], cmd);
		// 	return ;
		// }
		// ft_free(cmd);
		execcommand(cmd_tab->cmd, data);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		// waitpid(pid, NULL, 0);
	}
}

void	execution(t_cmd_tab  *cmd_tab, t_data *data, int nop)
{
	dup2(cmd_tab->in_fd, STDIN_FILENO);
	close(cmd_tab->in_fd);
	while (nop > 0)
	{
		child_process(cmd_tab, data);
		cmd_tab = cmd_tab->next;
		nop--;
	}
	dup2(cmd_tab->out_fd, STDOUT_FILENO);
	close(cmd_tab->out_fd);
	execcommand(cmd_tab->cmd, data);
}

// void	print_lexlst(t_lexer *lexer)
// {
// 	int	i;

// 	i = 0;
// 	while (lexer)
// 	{
// 		if (lexer->type == CMD)
// 			printf("lex[%i]=[%s]-[CMD]\n", i++, lexer->str);
// 		else if (lexer->type == ARGS)
// 			printf("lex[%i]=[%s]-[ARGS]\n", i++, lexer->str);
// 		else if (lexer->type == PIPE)
// 			printf("lex[%i]=[%s]-[PIPE]\n", i++, lexer->str);
// 		else if (lexer->type == FILES_IN)
// 			printf("lex[%i]=[%s]-[INFILE]\n", i++, lexer->str);
// 		else if (lexer->type == FILES_OUT)
// 			printf("lex[%i]=[%s]-[OUTFILE]\n", i++, lexer->str);
// 		else if (lexer->type == REDIR_IN)
// 			printf("lex[%i]=[%s]-[REDIR_IN]\n", i++, lexer->str);
// 		else if (lexer->type == REDIR_OUT)
// 			printf("lex[%i]=[%s]-[REDIR_OUT]\n", i++, lexer->str);
// 		else if (lexer->type == APPEND_IN)
// 			printf("lex[%i]=[%s]-[APPEND_IN]\n", i++, lexer->str);
// 		else if (lexer->type == APPEND_OUT)
// 			printf("lex[%i]=[%s]-[APPEND_OUT]\n", i++, lexer->str);
// 		// printf("lex[%i]=[%s]-[%d]\n", i++, lexer->str, lexer->type);
// 		if (!lexer->next)
// 			break;
// 		lexer = lexer->next;
// 	}
// }

void	exec_pipe(t_data *data, char **lex, int nop)
{
	t_lexer		*lexer;
	t_cmd_tab	*cmd_tab;
	int			pid;

	lexer = init_lex(lex);
	// print_lexlst(lexer);
	cmd_tab = init_cmd_tab(lexer, nop);
	// printf("IN_ID%d\n", cmd_tab->in_fd);
	// print_all_cmd_tab(cmd_tab);
	pid = fork();
	if (pid == 0)
		execution(cmd_tab, data, nop);
	// wait(&pid);
	waitpid(pid, NULL, 0);
	free_cmd_tab(cmd_tab);
	free_lex(lexer);
}
