#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include "colors.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

/* STRUCTURE */
typedef struct s_data
{
	char	**argv;
	char	**envp;
	int		argc;
	int		nb_cmd;
	int		nb_pipe;
	int		**pipe;
	pid_t	child[100];
}			t_data;

/* PROTOTYPES */

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

//newpipe.c
void	newpipe(t_data *data);
void	close_pipe(t_data *data);

//ft_split.c
char	**ft_split(char const *str, char charset);

//utils.c
void	ft_free(char **tab);
void	freeall(char **cmd, char **paths, char *bin);
t_data	get_args(int argc, char **argv);
t_data	get_envp(char **envp);
void	ft_error(const char *str);

#endif