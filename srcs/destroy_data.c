/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:11:46 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 10:58:52 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lex(t_lexer *lexer)
{
	t_lexer	*aux;

	while (lexer != NULL)
	{
		aux = lexer;
		lexer = lexer->next;
		ft_free((void **)&aux);
	}
	lexer = NULL;
}

void	free_parser(t_parser *parser, int nb_cmd)
{
	int	i;

	if (parser->cmds)
	{
		i = 0;
		while (i < nb_cmd)
		{
			free(parser->cmds[i].cmd);
			i++;
		}
		free(parser->cmds);
	}
	if (parser->redir)
	{
		i = 0;
		while (i < parser->size_redir)
		{
			free(parser->redir[i].files);
			i++;
		}
		free(parser->redir);
	}
}

void	free_exec(t_exec *exec, int nb_pipe)
{
	int	i;

	i = 0;
	if (exec->to_free)
		free(exec->to_free);
	while (i < exec->size)
	{
		free(exec->envp_s[i].key);
		free(exec->envp_s[i].value);
		i++;
	}
	free(exec->envp_s);
	i = 0;
	while (i < nb_pipe)
	{
		free(exec->pipes[i]);
		i++;
	}
	free(exec->pipes);
	free(exec->pid);
}

void	destroy_data(t_data *data, int mode)
{
	char	**tmp;

	tmp = data->envp;
	if (mode == DESTROY_ENV && data->envp)
		free_array(data->envp);
	if (data->lexer)
		free_lex(data->lexer);
	if (data->parser.cmds || data->parser.redir)
		free_parser(&data->parser, data->nb_cmd);
	if (data->exec.pid || data->exec.envp_s || data->exec.pipes)
		free_exec(&data->exec, data->nb_pipe);
	if (data->to_free && mode == DESTROY_ENV)
		free_array(data->to_free);
	if (mode == DONT_DESTROY_ENV)
	{
		ft_bzero(data, sizeof(t_data));
		data->envp = tmp;
	}
	else
		ft_bzero(data, sizeof(t_data));
}

void	malloc_error(t_data *data)
{
	destroy_data(data, DESTROY_ENV);
	write(2, "minishell: malloc error\n", 24);
	exit(1);
}
