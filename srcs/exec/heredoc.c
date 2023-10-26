/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:36:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 11:44:04 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	ft_change_char(int c)
{
	if (c < 0)
		c = -c;
	while (c > 122)
		c -= 26;
	if (c < 32)
		c += 32;
	if (c == ' ')
		c = '_';
	if (c == '/')
		c = '_';
	if (c == '.')
		c = '_';
	if (c == '$')
		c = '_';
	return (c);
}

// malloc a random string with nb_char characters
// return the string or NULL if an error occured
static
char	*random_name(int nb_char)
{
	int		fd_random;
	char	*buf;
	int		i;

	buf = ft_calloc(nb_char + 1, sizeof(char));
	if (!buf)
		return (NULL);
	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (NULL);
	if (read(fd_random, buf, nb_char) == -1)
		return (NULL);
	i = 0;
	while (i < (nb_char))
	{
		buf[i] = ft_change_char(buf[i]);
		i++;
	}
	close(fd_random);
	return (buf);
}

static
int	init_heredoc(t_heredoc *heredoc, t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == HEREDOC)
		{
			heredoc->delimiter = lexer->str;
			if (!heredoc->delimiter)
				return (EXIT_FAILURE);
			heredoc->name_file = random_name(10);
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
		runheredocchild(heredoc, data, all_h, size);
	waitpid(pid, &data->exec.status, 0);
	free(heredoc.delimiter);
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
		run_heredoc(heredoc[i], data, heredoc, nb_heredoc);
	return (EXIT_SUCCESS);
}
