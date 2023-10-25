/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/25 14:24:42 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(char **lex)
{
	int	i;

	if (lex == NULL)
		return ;
	i = 0;
	while (lex[i] != NULL)
	{
		free(lex[i]);
		i++;
	}
	free(lex);
}

void	print_lexer(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		printf("lex[%d]=[%s]\n", i, lex[i]);
		i++;
	}
}

char	**get_empty_lexer(void)
{
	char	**empty_lex;

	empty_lex = ft_calloc(1, sizeof(char *));
	if (empty_lex == NULL)
		return (NULL);
	empty_lex[0] = NULL;
	return (empty_lex);
}

char	**lexer(t_data *data, char *str)
{
	char	**lex;
	int		nb_token;

	nb_token = count_token(str);
	if (nb_token < 0)
		return (get_empty_lexer());
	lex = ft_calloc(nb_token + 1, sizeof(char *));
	if (lex == NULL)
		return (get_empty_lexer(), malloc_error(data), NULL);
	if (split_lexer(lex, str) == 0)
		return (free_lexer(lex), get_empty_lexer());
	if (check_lexer(lex) == 0)
		return (free_lexer(lex), get_empty_lexer(), NULL);
	return (lex);
}
