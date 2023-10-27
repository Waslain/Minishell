/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:36:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 16:54:01 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(t_heredoc *heredoc, int nb_heredoc)
{
	int	i;

	i = 0;
	while (i < nb_heredoc)
	{
		ft_free((void **)&heredoc[i].name_file);
		i++;
	}
	ft_free((void **)&heredoc);
}

void	destroy_all_heredoc(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_heredoc)
	{
		unlink(data->heredoc[i].name_file);
		i++;
	}
}

static
char	*name_file_heredoc(int n, t_data *data)
{
	char	*str_itoa;
	char	*name_file;

	str_itoa = ft_itoa(n);
	if (!str_itoa)
		return (malloc_error(data), NULL);
	name_file = ft_strjoin("/tmp/.heredoc_", str_itoa);
	if (!name_file)
		return (ft_free((void **)&str_itoa), malloc_error(data), NULL);
	ft_free((void **)&str_itoa);
	return (name_file);
}

static
int	init_heredoc(t_heredoc *heredoc, t_lexer *lexer, t_data *data)
{
	static int	n;
	int			i;

	i = 0;
	while (lexer)
	{
		if (lexer->type == HEREDOC && i < data->nb_heredoc)
		{
			heredoc[i].delimiter = lexer->str;
			heredoc[i].name_file = name_file_heredoc(n, data);
			lexer->str = heredoc[i].name_file;
			n++;
			i++;
		}
		lexer = lexer->next;
	}
	return (EXIT_SUCCESS);
}

static
void	run_heredoc(t_heredoc *heredoc, t_data *data)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < data->nb_heredoc)
	{
		pid = fork();
		if (pid == 0)
		{
			mode_signal(S_HEREDOC);
			run_heredoc_child(heredoc[i], data);
			exit(0);
		}
		else
			waitpid(pid, NULL, 0);
		i++;
	}
}

int	heredoc(t_data *data)
{
	data->nb_heredoc = count_type_token(data->lexer, HEREDOC);
	if (data->nb_heredoc == 0)
		return (EXIT_SUCCESS);
	data->heredoc = ft_calloc(sizeof(t_heredoc), data->nb_heredoc);
	if (!data->heredoc)
		return (EXIT_FAILURE);
	if (init_heredoc(data->heredoc, data->lexer, data))
		return (EXIT_FAILURE);
	run_heredoc(data->heredoc, data);
	return (EXIT_SUCCESS);
}
