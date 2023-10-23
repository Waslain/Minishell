/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/23 11:26:22 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include "colors.h"
# include "parser.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

/* STRUCTURE */
typedef struct s_data
{
	char	*cmd;
	char	**envp;
	int		nb_cmd;
	int		nb_pipe;
}			t_data;

/*					LEXER FUNCTIONS						*/
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

/*					EXEC FUNCTIONS						*/
void		print_error(char *str);

//exec/exec_cmd.c
void		execsimplecommand(t_data *data);
void		execcommand(char *str, t_data *data);

//exec/exec_pipe.c
void		exec_pipe(t_data *data, char **lex, int nop);
//exec/exec_no_pipe.c
void		exec_no_pipe(t_data *data, char **lex);
//Builtin/builtin.c
int			is_builtin(char *str);
int			exec_builtin(t_data *data, char *cmd, char **str);
//Builtin/echo.c
void		builtin_echo(char **str);
//Builtin/pwd.c
int			builtin_pwd(void);
//Builtin/env.c
void		builtin_env(t_data *data);
//Builtin/exit.c
void		builtin_exit(void);

//exec.c
char		*get_bin(char *cmd, char **paths);
char		*get_line(t_data *data);
char		**get_paths(t_data *data);

//libft.c
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);

//libft1.c
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_isalpha(int c);

//ft_split.c
char		**ft_split(char const *str, char charset);

//utils.c
void		ft_free(char **tab);
void		freeall(char **cmd, char **paths, char *bin);
t_data		*get_envp(t_data *data, char **envp);
void		ft_error(const char *str);

//signals.c
void		init_signal(void);
void		init_signal2(void);

#endif