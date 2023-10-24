/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:39:06 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 12:34:57 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "library.h"
# include "struct.h"

int		main_exec(t_data *data);

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