/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 11:51:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "library.h"
# include "struct.h"

t_lexer		*init_lex(char **lex);
void		free_lex(t_lexer *lexer);
t_cmd_tab	*init_cmd_tab(t_lexer *lexer, int nop);
t_lexer		*parse_cmd_tab(t_cmd_tab *cmd_tab, t_lexer *lexer);
void		free_cmd_tab(t_cmd_tab *cmd_tab);
#endif