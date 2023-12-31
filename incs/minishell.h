/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:57:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/29 15:49:24 by fduzant          ###   ########.fr       */
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

enum e_no_run
{
	EXPORT,
	CD,
	UNSET
};

int		minishell_loop(t_data *data);

enum e_mode
{
	SAVE,
	DESTROY
};

int		heredoc(t_data *data);
void	run_heredoc_child(t_heredoc hd, t_data *data);
void	ctrl_c_heredoc(t_heredoc hd, t_data *data, int mode);
void	unlink_all_heredoc(t_data *data);
void	free_heredoc(t_heredoc *heredoc, int nb_heredoc);

enum e_signal
{
	S_MAIN,
	S_CHILD,
	S_HEREDOC,
	S_PARENT
};

void	update_status_with_signal(int *status);
void	block_signal(int signal);
void	unblock_signal(int signal);
void	handler_quit(int signal);
void	handler_end_spe(int signal1);
void	handler_end(int signal);
void	mode_signal(int mode);

void	destroy_data(t_data *data, int mode);
void	malloc_error(t_data *data);

void	print_lexlst(t_lexer *lexer);
char	*found_token(int token);

void	destroy_data(t_data *data, int mode);
void	print_cmds_struct(t_data *data);
void	print_redir_struct(t_data *data);
void	print_envp_struct(t_envp *envp, int size);

#endif