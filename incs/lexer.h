/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:34:33 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 11:44:58 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "library.h"
# include "struct.h"

int			is_white_space(char c);
int			is_spec_char(char c);
int			is_quote(char c);
int			count_token(char *str);
void		go_next_quote(char	*str, int *i, char quote);
void		skip_white_space(char *str, int *i);
void		skip_token(char *str, int *i);
int			split_lexer(char **lex, char *str);
char		**lexer(char *str);
void		free_lexer(char **lex);
void		print_lexer(char **lex);
int			check_lexer(char **lex);
int			is_delimiter(char *lex);
char		**clearquotes(char **lex);
char		**clear_lex(t_data *data, char *rl);
char		*get_env_var(t_data *data, char *find);
char		*expandlex(t_data *data, char *lex);
char		*ft_strjoinn(char const *s1, char const *s2, int n);
char		*ft_strndup(const char *src, int x);
int			skip_to_dollars(char *lex);
void		free_for_expand(char *find, char *findval);
void		free_for_expand_all(char *tmp, char *find, char *findval);
#endif