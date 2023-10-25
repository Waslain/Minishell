/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/25 10:22:49 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "library.h"
# include "struct.h"

t_lexer		*init_lex(char **lex);
void		free_lex(t_lexer *lexer);

int			main_parser(t_data *data);
int			init_cmds(t_data *data);
int			init_redir(t_data *data);

bool		is_redir_in(int token);
bool		is_redir_out(int token);
bool		is_infile(int token);
bool		is_outfile(int token);
bool		is_file(int token);
#endif