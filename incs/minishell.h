/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:57:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/26 11:26:43 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "exec.h"
# include "lexer.h"
# include "library.h"
# include "parser.h"
# include "signal.h"
# include "token.h"
# include "utils.h"

enum e_error
{
	EXIT_MINISHELL = 2,
	EMPTY_COMMANDE = 1,
	NO_ERROR = 0
};

enum e_destroy
{
	DESTROY_ENV,
	DONT_DESTROY_ENV
};

int		count_type_token(t_lexer *lexer, int type);
int		minishell_loop(t_data *data);
int		minishell(t_data *data);

int		heredoc(t_data *data);
void	runheredocchild(t_heredoc hd, t_data *data, t_heredoc *all_h, int size);

void	init_signal(void);
void	init_signal2(void);

void	destroy_data(t_data *data, int mode);
void	malloc_error(t_data *data);

void	print_lexlst(t_lexer *lexer);
char	*found_token(int token);

void	destroy_data(t_data *data, int mode);
void	print_cmds_struct(t_data *data);
void	print_redir_struct(t_data *data);
void	print_envp_struct(t_envp *envp, int size);

#endif