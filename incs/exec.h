/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:39:06 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 10:36:40 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "library.h"
# include "struct.h"

enum e_stdfd
{
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2
};

enum e_redir
{
	NO_FILE = -2,
	ERROR_FILE = -1
};

# define HEREDOC_MSG_CTRL_D "minishell: warning: here-document delimited by end-of-file \
(wanted `"
# define ERROR_WRITE "write error: No space left on device"

int		main_exec(t_data *data);

int		parent_no_cmd_redir(t_data *data);
int		parent_simple_cmd(t_data *data);
int		parent_pipe(t_data *data);
int		parent_pipe_redir(t_data *data);
int		parent_redir(t_data *data);

void	child_no_cmd_redir(t_data *data);
void	child_redir(t_data *data);
void	child_pipe(t_data *data);
void	child_pipe_redir(t_data *data);

int		ft_open(char *name, int type);
int		open_infile(t_file *file, int size, t_data *data);
int		open_outfile(t_file *file, int size, t_data *data);

void	ft_execve(t_data *data);

void	ft_close(int *fd);
void	close_all_pipe(int **pipes, int nb_pipe);

char	*get_key(char *str);
char	*get_value(char *str);
int		conv_env_to_struct(char **envp, t_envp **envp_s, int *size);
int		conv_env_struct_to_env(char ***envp, t_envp *envp_s, int size);

char	*found_value_with_key(t_envp *envp, char *key, int size);
int		found_index_with_key(t_envp *envp, char *key, int size);
int		update_value_with_key(t_envp *envp_s, int *size, char *key, char *val);
int		add_key_value(t_envp **envp_s, int *size, char *key, char *value);
int		delete_key_value(t_envp **envp_s, int *size, char *key);

void	error_child(t_data *data, const char *arg, const char *msg, int val);

// BUILTINS
bool	is_in_child(t_data *data);
bool	is_in_parent(t_data *data);
int		builtin_in_child(t_data *data);
int		builtin_in_parent(t_data *data);
int		count_args(const char **cmds);

int		echo(t_data *data, const int id);
int		env(t_data *data, const int id);
int		pwd(t_data *data, const int id);
int		export(t_data *data);
int		unset(t_data *data);
int		cd(t_data *data);
#endif