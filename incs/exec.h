/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:39:06 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 10:27:40 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "library.h"
# include "struct.h"

int		main_exec(t_data *data);

int		parent_no_cmd_redir(t_data *data);
int		parent_simple_cmd(t_data *data);
int		parent_pipe(t_data *data);
int		parent_pipe_redir(t_data *data);
int		parent_redir(t_data *data);

void	child_no_cmd_redir(t_data *data);
void	child_pipe(t_data *data);
void	child_pipe_redir(t_data *data);
void	child_redir(t_data *data);

int		ft_open(char *name, int type);
int		open_infile(t_file *file, int size);
int		open_outfile(t_file *file, int size);

void	ft_execve(t_data *data);

void	ft_close(int *fd);
void	close_all_pipe(int pipes[2][2]);

//Builtin/builtin.c
int		is_builtin(char *str);
int		exec_builtin(t_data *data, char *cmd, char **str);
//Builtin/echo.c
void	builtin_echo(char **str);
//Builtin/pwd.c
int		builtin_pwd(void);
//Builtin/env.c
void	builtin_env(t_data *data);
//Builtin/exit.c
void	builtin_exit(void);
#endif