#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include "colors.h"
# include "parser.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

extern int	g_error;

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

/*					EXEC FUNCTIONS						*/
void		print_error(char *str);

//exec.c
char	*get_bin(char *cmd, char **paths);
char	*get_line(t_data *data);
char	**get_paths(t_data *data);

//libft.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//libft1.c
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strcmp(char *s1, char *s2);

//newpipe.c
void	newpipe(t_data *data);
void	close_pipe(t_data *data);

//ft_split.c
char	**ft_split(char const *str, char charset);

//utils.c
void	ft_free(char **tab);
void	freeall(char **cmd, char **paths, char *bin);
t_data	get_envp(char **envp);
void	ft_error(const char *str);

#endif