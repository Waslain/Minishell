/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:36:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 15:41:10 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	init_heredoc(t_heredoc *heredoc, t_lexer *lexer)
{
	const char	*name = "/tmp/.heredoc_";

	while (lexer)
	{
		if (lexer->type == HEREDOC)
		{
			heredoc->delimiter = lexer->str;
			if (!heredoc->delimiter)
				return (EXIT_FAILURE);
			heredoc->name_file = (char *)name;
			if (!heredoc->name_file)
				return (EXIT_FAILURE);
			lexer->str = heredoc->name_file;
		}
		lexer = lexer->next;
	}
	return (EXIT_SUCCESS);
}

static
void	run_heredoc(t_heredoc heredoc, t_data *data, t_heredoc *all_h, int size)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		mode_signal(S_HEREDOC);
		runheredocchild(heredoc, data, all_h, size);
		exit(0);
	}
	waitpid(pid, &data->exec.status, 0);
}

int	heredoc(t_data *data)
{
	t_heredoc	*heredoc;
	int			nb_heredoc;
	int			i;

	nb_heredoc = count_type_token(data->lexer, HEREDOC);
	if (nb_heredoc == 0)
		return (EXIT_SUCCESS);
	heredoc = ft_calloc(sizeof(t_heredoc), nb_heredoc);
	if (!heredoc)
		return (EXIT_FAILURE);
	if (init_heredoc(heredoc, data->lexer))
		return (EXIT_FAILURE);
	print_lexlst(data->lexer);
	i = 0;
	while (i < nb_heredoc)
		run_heredoc(heredoc[i++], data, heredoc, nb_heredoc);
	free(heredoc);
	return (EXIT_SUCCESS);
}
