/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# define FILES_IN 0
# define FILES_OUT 1
# define HEREDOC 2
# define PIPE 3
# define CMD 4
# define ARGS 5
# define SIMPLE_QUOTE 6
# define DOUBLE_QUOTE 7
# define REDIR_IN 8
# define REDIR_OUT 9
# define APPEND_IN 10
# define APPEND_OUT 11

/* STRUCTURE */
typedef struct s_lexer
{
	char				*str;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_cmd_tab
{
	int					in_fd;
	int					out_fd;
	char				*cmd;
	struct s_cmd_tab	*next;
}	t_cmd_tab;

t_lexer		*init_lex(char **lex);
void		free_lex(t_lexer *lexer);
t_cmd_tab	*init_cmd_tab(t_lexer *lexer, int nop);
t_lexer		*parse_cmd_tab(t_cmd_tab *cmd_tab, t_lexer *lexer);
void		free_cmd_tab(t_cmd_tab *cmd_tab);
void		check_fd_open(int fd);
void		open_infile(t_cmd_tab *cmd_tab, t_lexer *lexer);
void		open_outfile(t_cmd_tab *cmd_tab, t_lexer *lexer);
#endif